/*
 * Copyright (c) 2019 TAOS Data, Inc. <jhtao@taosdata.com>
 *
 * This program is free software: you can use, redistribute, and/or modify
 * it under the terms of the GNU Affero General Public License, version 3
 * or later ("AGPL"), as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "gateSystem.h"
#include "modbusTcp.h"
#include "modbusRtu.h"
#include "tcrc32c.h"
#include "taos.h"
#include "tlog.h"
#include "tutil.h"

typedef struct {
  void *     signature;
  char       name[TSDB_METER_ID_LEN];
  int        mseconds;
  uint64_t   lastKey;
  uint64_t   stime;
  TAOS_FIELD fields[TSDB_MAX_COLUMNS];
  int        numOfFields;
  TAOS *     taos;
  TAOS_RES * result;
} SSub;

GModule         lmModule[GATE_MOD_MAX];

//pthread_mutex_t dmutex;
TAOS *pTaosConn;
GATE_INFO gGate = {0};

void gateInitModules() {
	lmModule[GATE_MODBUS_TCP].name = "modbus_tcp";
	lmModule[GATE_MODBUS_TCP].initFp = modbusTcpInitSystem;
	lmModule[GATE_MODBUS_TCP].cleanUpFp = modbusTcpCleanUpSystem;
	lmModule[GATE_MODBUS_TCP].startFp = modbusTcpStartSystem;
	lmModule[GATE_MODBUS_TCP].stopFp = modbusTcpStopSystem;
	lmModule[GATE_MODBUS_TCP].enable = gGate.enableModbusTcp;


	lmModule[GATE_MODBUS_RTU].name = "modbus_rtu";
	lmModule[GATE_MODBUS_RTU].initFp = modbusRtuInitSystem;
	lmModule[GATE_MODBUS_RTU].cleanUpFp = modbusRtuCleanUpSystem;
	lmModule[GATE_MODBUS_RTU].startFp = modbusRtuStartSystem;
	lmModule[GATE_MODBUS_RTU].stopFp = modbusRtuStopSystem;
	lmModule[GATE_MODBUS_RTU].enable = gGate.enableModbusRtu;
}

void gateCleanUpSystem() {
	if (pTaosConn != NULL) {
		taos_close(pTaosConn);
	}

	for (int mod = 0; mod < GATE_MOD_MAX; ++mod) {
		if (lmModule[mod].enable != 0 && lmModule[mod].stopFp) (*lmModule[mod].stopFp)();
		if (lmModule[mod].enable != 0 && lmModule[mod].cleanUpFp) (*lmModule[mod].cleanUpFp)();
	}
}

int queryGateInfo(GATE_INFO* pGate){
	char     qstr[128];

	//sprintf(qstr, "UPDATE GATE g002 '{enable:true,ddd:13300}'");
	//sprintf(qstr,"CREATE GATE g003 '{enable:true,ddd:100}'");
	sprintf(qstr, "QUERY GATE g003");
	//sprintf(qstr, "DELETE GATE g003");
	if (taos_query(pTaosConn, qstr)) {
		return -1;
	}


/*	sprintf(qstr,"select * from lm_gate where name = '%s'",tsGateName);
	if (taos_query(pTaosConn, qstr)) {
		return -1;
	}

	TAOS_RES* result = taos_use_result(pTaosConn);
	if (result == NULL) {
		return -1;
	}

	TAOS_ROW row = taos_fetch_row(result);
	if(row == NULL){
		taos_free_result(result);
		return -1;
	}

	int         num_fields = taos_field_count(pTaosConn);
	TAOS_FIELD *fields = taos_fetch_fields(result);
	for (int i = 0; i < num_fields; ++i) {
		if(strcmp(fields[i].name,"modbus_tcp") == 0){
			pGate->enableModbusTcp = *((int8_t *)row[i]);
		}else if(strcmp(fields[i].name,"modbus_rtu") == 0){
			pGate->enableModbusRtu = *((int8_t *)row[i]);
		}
	}
	taos_free_result(result);*/

	return 0;
}


int gateInitSystem() {
	char     qstr[128];

	tprintf("gateInitSystem ", 255,"starting to initialize gate engine ...");

	taos_init();
	pTaosConn = taos_connect(NULL, tsDefaultUser, tsDefaultPass, tsDefaultDB, 0);
	if (pTaosConn == NULL) {
		tprintf("gateInitSystem ", 255,"Failed to connect to TDengine, reason:%s\n", taos_errstr(pTaosConn));
		return -1;
	}

	sprintf(qstr,"use %s",tsDefaultDB);
	if (taos_query(pTaosConn, qstr)) {
		tprintf("gateInitSystem ", 255,"Failed to use, reason:%s\n", taos_errstr(pTaosConn));
		return -1;
	}

	if(queryGateInfo(&gGate) != 0){
		tprintf("gateInitSystem ", 255,"Failed to queryGateInfo, reason:%s\n", taos_errstr(pTaosConn));
		return -1;
	}

	gateInitModules();
	for (int mod = 0; mod < GATE_MOD_MAX; ++mod) {
		if(lmModule[mod].enable != 1)
			continue;

		if ((*lmModule[mod].initFp)() != 0) {
			tprintf("gateInitSystem ", 255,"module:%s initialization failed",lmModule[mod].name);
			return -1;
		}

		if ((*lmModule[mod].startFp)() != 0) {
			tprintf("gateInitSystem ", 255,"failed to start module:%s", lmModule[mod].name);
			return -1;
		}
	}

	tprintf("gateInitSystem ", 255,"gate engine is initialized successfully");

	return 0;
}

SSub *subscribe(char *name, int mseconds) {
	SSub *pSub;
	struct timeval systemTime;

	pSub = (SSub *)malloc(sizeof(SSub));
	if (pSub == NULL) return NULL;
	memset(pSub, 0, sizeof(SSub));

	pSub->taos = pTaosConn;
	pSub->signature = pSub;
	strcpy(pSub->name, name);
	pSub->mseconds = mseconds;

	gettimeofday(&systemTime, NULL);
	pSub->lastKey = (uint64_t)systemTime.tv_sec * 1000LL + (uint64_t)systemTime.tv_usec / 1000;

	char qstr[128];
	sprintf(qstr, "select * from %s where _c0 > now+1000d", pSub->name);
	if (taos_query(pSub->taos, qstr)) {
		tprintf("subscribe ", 255,"failed to select, reason:%s", taos_errstr(pSub->taos));
		tfree(pSub);
		return NULL;
	}
	pSub->result = taos_use_result(pSub->taos);
	pSub->numOfFields = taos_num_fields(pSub->result);
	memcpy(pSub->fields, taos_fetch_fields(pSub->result), sizeof(TAOS_FIELD) * pSub->numOfFields);

	return pSub;
}

TAOS_ROW consume(TAOS_SUB *tsub) {
	SSub *   pSub = (SSub *)tsub;
	TAOS_ROW row;
	char     qstr[256];
	struct timeval systemTime;

	if (pSub == NULL) return NULL;
	if (pSub->signature != pSub) return NULL;

	while (1) {
		if (pSub->result != NULL) {
			row = taos_fetch_row(pSub->result);
			if (row != NULL) {
				pSub->lastKey = *((uint64_t *)row[0]);
				return row;
			}

			taos_free_result(pSub->result);
			pSub->result = NULL;

			gettimeofday(&systemTime, NULL);
			uint64_t etime = (uint64_t)systemTime.tv_sec * 1000LL + (uint64_t)systemTime.tv_usec / 1000;

			//uint64_t etime = taosGetTimestampMs();
			int64_t  mseconds = pSub->mseconds - etime + pSub->stime;
			if (mseconds < 0) mseconds = 0;
			taosMsleep((int)mseconds);
		}

		gettimeofday(&systemTime, NULL);
		pSub->stime = (uint64_t)systemTime.tv_sec * 1000LL + (uint64_t)systemTime.tv_usec / 1000;

		//pSub->stime = taosGetTimestampMs();

		sprintf(qstr, "select * from %s where _c0 > %lld order by _c0 asc", pSub->name, pSub->lastKey);
		if (taos_query(pSub->taos, qstr)) {
			tprintf("consume ", 255,"failed to select, reason:%s", taos_errstr(pSub->taos));
			return NULL;
		}

		pSub->result = taos_use_result(pSub->taos);

		if (pSub->result == NULL) {
			tprintf("consume ", 255,"failed to get result, reason:%s", taos_errstr(pSub->taos));
			return NULL;
		}
	}

	return NULL;
}

int handleMessage(const SSub* const pSub, const TAOS_ROW const row){
	for (int i = 0; i < pSub->numOfFields; ++i) {
		if(strcmp(pSub->fields[i].name,"message") == 0){
			tprintf("handleMessage ", 255,"handle message:%s",row[i]);
		}
	}


	return 0;
}

int gateStartSystem(){
	TAOS_SUB* pSub = subscribe("lm_message",1000);
	if(pSub == NULL){
		tprintf("gateStartSystem ", 255,"Failed to subscribe, reason:%s\n", taos_errstr(pTaosConn));
		gateCleanUpSystem();
		return -1;
	}
	while (1) {
		TAOS_ROW row = consume(pSub);
		if(row == NULL){
			tprintf("gateStartSystem ", 255,"Failed to subscribe, reason:%s\n", taos_errstr(pTaosConn));
			break;
		}
		handleMessage(pSub,row);
	}
	free(pSub);
	gateCleanUpSystem();

	return 0;
}


