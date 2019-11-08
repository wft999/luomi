
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "taos.h"
#include "tutil.h"
#include "lmdb.h"

#define MAX_MODBUS_TCP_NUM 10

typedef struct {
  void *    signature;
  char      name[64];
  char		ip[64];
  int		port;
} MODBUS_TCP_CONN;

typedef struct {
  void *    		signature;
  TAOS *			pTaosConn;
  MODBUS_TCP_CONN 	conns[MAX_MODBUS_TCP_NUM];
  int 				totalConn;
} MODBUSTCP;

MODBUSTCP mod={0};
int modbusTcpInitSystem() {
	char     qstr[128];

	mod.pTaosConn = taos_connect(NULL, tsDefaultUser, tsDefaultPass, tsDefaultDB, 0);
	if (mod.pTaosConn == NULL) {
		tprintf("modbusTcpInitSystem ", 255,"Failed to connect to TDengine, reason:%s\n", taos_errstr(mod.pTaosConn));
		return -1;
	}

	sprintf(qstr,"use %s",tsDefaultDB);
	if (taos_query(mod.pTaosConn, qstr)) {
		tprintf("modbusTcpInitSystem ", 255,"Failed to use, reason:%s\n", taos_errstr(mod.pTaosConn));
		return -1;
	}

	sprintf(qstr,"select * from lm_modbus_tcp where name like '%s.%%' and enable=true",tsGateName);
	if (taos_query(mod.pTaosConn, qstr)) {
		tprintf("modbusTcpInitSystem ", 255,"Failed to select, reason:%s\n", taos_errstr(mod.pTaosConn));
		return -1;
	}

	TAOS_RES* result = taos_use_result(mod.pTaosConn);
	if (result == NULL) {
		return -1;
	}

	int         num_fields = taos_field_count(mod.pTaosConn);
	TAOS_FIELD *fields = taos_fetch_fields(result);

	TAOS_ROW row;
	while ((row = taos_fetch_row(result))) {
		MODBUS_TCP_CONN* pConn = mod.conns + mod.totalConn;
		for (int i = 0; i < num_fields; ++i) {
			if(strcmp(fields[i].name,"name") == 0){
				strcpy(pConn->name,(char*)row[i]);
			}else if(strcmp(fields[i].name,"server_ip") == 0){
				strcpy(pConn->ip,(char*)row[i]);
			}else if(strcmp(fields[i].name,"port") == 0){
				pConn->port = *((int32_t *)row[i]);
			}
		}
		mod.totalConn++;
		if(mod.totalConn > MAX_MODBUS_TCP_NUM){
			tprintf("modbusTcpInitSystem ", 255,"mod.totalConn > MAX_MODBUS_TCP_NUM\n");
			break;
		}

	}

	taos_free_result(result);

	return 0;
}

int modbusTcpStartSystem() {

	return 0;
}


void modbusTcpStopSystem() {

}

void modbusTcpCleanUpSystem() {
	if (mod.pTaosConn != NULL) {
		taos_close(mod.pTaosConn);
	}

}

