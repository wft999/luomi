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

#include <arpa/inet.h>

#include "lmdb.h"
#include "tschemautil.h"
#include "mgmt.h"

extern int (*mgmtProcessShellMsg[TSDB_MSG_TYPE_MAX])(char *, int, SConnObj *);
int mgmtProcessCreateGateMsg(char *pMsg, int msgLen, SConnObj *pConn);
int mgmtProcessQueryGateMsg(char *pMsg, int msgLen, SConnObj *pConn);
int mgmtProcessDeleteGateMsg(char *pMsg, int msgLen, SConnObj *pConn);
int mgmtProcessUpdateGateMsg(char *pMsg, int msgLen, SConnObj *pConn);

void *gateSdb = NULL;
int   tsGateUpdateSize;

void *(*mgmtGateActionFp[SDB_MAX_ACTION_TYPES])(void *row, char *str, int size, int *ssize);
void *mgmtGateActionInsert(void *row, char *str, int size, int *ssize);
void *mgmtGateActionDelete(void *row, char *str, int size, int *ssize);
void *mgmtGateActionUpdate(void *row, char *str, int size, int *ssize);
void *mgmtGateActionEncode(void *row, char *str, int size, int *ssize);
void *mgmtGateActionDecode(void *row, char *str, int size, int *ssize);
void *mgmtGateActionBeforeBatchUpdate(void *row, char *str, int size, int *ssize);
void *mgmtGateActionBatchUpdate(void *row, char *str, int size, int *ssize);
void *mgmtGateActionAfterBatchUpdate(void *row, char *str, int size, int *ssize);
void *mgmtGateActionReset(void *row, char *str, int size, int *ssize);
void *mgmtGateActionDestroy(void *row, char *str, int size, int *ssize);

void mgmtGateActionInit() {
  mgmtGateActionFp[SDB_TYPE_INSERT] = mgmtGateActionInsert;
  mgmtGateActionFp[SDB_TYPE_DELETE] = mgmtGateActionDelete;
  mgmtGateActionFp[SDB_TYPE_UPDATE] = mgmtGateActionUpdate;
  mgmtGateActionFp[SDB_TYPE_ENCODE] = mgmtGateActionEncode;
  mgmtGateActionFp[SDB_TYPE_DECODE] = mgmtGateActionDecode;
  mgmtGateActionFp[SDB_TYPE_BEFORE_BATCH_UPDATE] = mgmtGateActionBeforeBatchUpdate;
  mgmtGateActionFp[SDB_TYPE_BATCH_UPDATE] = mgmtGateActionBatchUpdate;
  mgmtGateActionFp[SDB_TYPE_AFTER_BATCH_UPDATE] = mgmtGateActionAfterBatchUpdate;
  mgmtGateActionFp[SDB_TYPE_RESET] = mgmtGateActionReset;
  mgmtGateActionFp[SDB_TYPE_DESTROY] = mgmtGateActionDestroy;

  mgmtProcessShellMsg[TSDB_MSG_TYPE_CREATE_GATE] = mgmtProcessCreateGateMsg;
  mgmtProcessShellMsg[TSDB_MSG_TYPE_QUERY_GATE] = mgmtProcessQueryGateMsg;
  mgmtProcessShellMsg[TSDB_MSG_TYPE_UPDATE_GATE] = mgmtProcessUpdateGateMsg;
  mgmtProcessShellMsg[TSDB_MSG_TYPE_DELETE_GATE] = mgmtProcessDeleteGateMsg;
}

void *mgmtGateAction(char action, void *row, char *str, int size, int *ssize) {
  if (mgmtGateActionFp[action] != NULL) {
    return (*(mgmtGateActionFp[action]))(row, str, size, ssize);
  }
  return NULL;
}

int mgmtInitGates() {
  mgmtGateActionInit();

  gateSdb = sdbOpenTable(TSDB_GATE_MAX_NUM, sizeof(SGateObj), "gate", SDB_KEYTYPE_STRING, mgmtDirectory, mgmtGateAction);
  if (gateSdb == NULL) {
    mError("failed to init gate data");
    return -1;
  }

  mTrace("gate data is initialized");
  return 0;
}

SGateObj *mgmtGetGate(char* name) {
	SGateObj *pGate = (SGateObj *)sdbGetRow(gateSdb, name);
	return pGate;
}

int mgmtUpdateGate(SAcctObj *pAcct,SGateObj *pGate) {
	int ret = sdbUpdateRow(gateSdb, pGate, 0, 1);
	return ret;
}

int mgmtCreateGate(SAcctObj *pAcct,SGateObj* pCreate) {
  SGateObj *pGate;

  int numOfGates = sdbGetNumOfRows(gateSdb);
  if (numOfGates >= TSDB_GATE_MAX_NUM) {
    mWarn("numOfGates:%d, exceed TSDB_GATE_MAX_NUM:%d", numOfGates, TSDB_GATE_MAX_NUM);
    return TSDB_CODE_TOO_MANY_GATES;
  }

  pGate = (SGateObj *)sdbGetRow(gateSdb, pCreate->name);
  if (pGate != NULL) {
     mWarn("gate:%s is already there", pCreate->name);
     return TSDB_CODE_INVALID_GATE;
  }

  if (sdbInsertRow(gateSdb, pCreate, 0) < 0) {
    return TSDB_CODE_SDB_ERROR;
  }

  return TSDB_CODE_SUCCESS;
}

int mgmtDropGate(SAcctObj* pAcct,char *name) {
  SGateObj *pGate;

  pGate = (SGateObj *)sdbGetRow(gateSdb, name);
  if (pGate == NULL) {
    mWarn("gate:%s is not there", name);
    return TSDB_CODE_INVALID_GATE;
  }

  sdbDeleteRow(gateSdb, pGate);

  return 0;
}

void mgmtCleanUpGates() { sdbCloseTable(gateSdb); }


void *mgmtGateActionInsert(void *row, char *str, int size, int *ssize) {
  return NULL;
}
void *mgmtGateActionDelete(void *row, char *str, int size, int *ssize) {
  return NULL;
}
void *mgmtGateActionUpdate(void *row, char *str, int size, int *ssize) {
  return mgmtGateActionReset(row, str, size, ssize);
}
void *mgmtGateActionEncode(void *row, char *str, int size, int *ssize) {
  SGateObj *pGate = (SGateObj *)row;
  int       tsize = pGate->updateEnd - (char *)pGate;
  if (size < tsize) {
    *ssize = -1;
  } else {
    memcpy(str, pGate, tsize);
    *ssize = tsize;
  }
  return NULL;
}
void *mgmtGateActionDecode(void *row, char *str, int size, int *ssize) {
  SGateObj *pGate = (SGateObj *)malloc(sizeof(SGateObj));
  if (pGate == NULL) return NULL;
  memset(pGate, 0, sizeof(SGateObj));

  int tsize = pGate->updateEnd - (char *)pGate;
  memcpy(pGate, str, tsize);
  return (void *)pGate;
}
void *mgmtGateActionBeforeBatchUpdate(void *row, char *str, int size, int *ssize) { return NULL; }
void *mgmtGateActionBatchUpdate(void *row, char *str, int size, int *ssize) { return NULL; }
void *mgmtGateActionAfterBatchUpdate(void *row, char *str, int size, int *ssize) { return NULL; }
void *mgmtGateActionReset(void *row, char *str, int size, int *ssize) {
  SGateObj *pGate = (SGateObj *)row;
  int       tsize = pGate->updateEnd - (char *)pGate;
  memcpy(pGate, str, tsize);

  return NULL;
}

void *mgmtGateActionDestroy(void *row, char *str, int size, int *ssize) {
  tfree(row);
  return NULL;
}

int mgmtProcessCreateGateMsg(char *pMsg, int msgLen, SConnObj *pConn) {
  int             code = 0;

  SGateObj *pCreate = (SGateObj *)pMsg;
  if (pConn->superAuth) {
    code = mgmtCreateGate(&acctObj, pCreate);
    if (code == TSDB_CODE_SUCCESS) {
      mLPrint("gate:%s is created by %s", pCreate->name, pConn->pUser->user);
    }
  } else {
    code = TSDB_CODE_NO_RIGHTS;
  }

  taosSendSimpleRsp(pConn->thandle, TSDB_MSG_TYPE_CREATE_GATE_RSP, code);

  return 0;
}

int mgmtProcessQueryGateMsg(char *pMsg, int msgLen, SConnObj *pConn) {
  STaosRsp *   pRsp;
  char *       pStart;
  int          code = 0;

  char* name = pMsg;

  int size = sizeof(STaosHeader) + sizeof(STaosRsp) + TSDB_GATE_SETTING_LEN + TSDB_EXTRA_PAYLOAD_SIZE;
  pStart = taosBuildRspMsgWithSize(pConn->thandle, TSDB_MSG_TYPE_QUERY_GATE_RSP, size);
  if (pStart == NULL) return 0;
  pMsg = pStart;
  pRsp = (STaosRsp *)pMsg;
  pMsg = (char *)pRsp->more;

  SGateObj* pGate = (SGateObj *)sdbGetRow(gateSdb, name);
  if (pGate == NULL) {
     mWarn("gate:%s is not there", name);
     return TSDB_CODE_INVALID_GATE;
  }
  strcpy(pMsg,pGate->setting);
  pMsg += strlen(pGate->setting)+1;

  pRsp->code = code;
  msgLen = pMsg - pStart;
  taosSendMsgToPeer(pConn->thandle, pStart, msgLen);

  return msgLen;
}

int mgmtProcessUpdateGateMsg(char *pMsg, int msgLen, SConnObj *pConn) {
  int             code = 0;

  SGateObj *pCreate = (SGateObj *)pMsg;
  if (pConn->superAuth) {
    code = mgmtUpdateGate(&acctObj, pCreate);
    if (code == TSDB_CODE_SUCCESS) {
      mLPrint("gate:%s is updated by %s", pCreate->name, pConn->pUser->user);
    }
  } else {
    code = TSDB_CODE_NO_RIGHTS;
  }

  taosSendSimpleRsp(pConn->thandle, TSDB_MSG_TYPE_QUERY_GATE_RSP, code);

  return 0;
}

int mgmtProcessDeleteGateMsg(char *pMsg, int msgLen, SConnObj *pConn) {
  int             code = 0;

  if (pConn->superAuth) {
    code = mgmtDropGate(&acctObj, pMsg);
    if (code == TSDB_CODE_SUCCESS) {
      mLPrint("gate:%s is deleted by %s", pMsg, pConn->pUser->user);
    }
  } else {
    code = TSDB_CODE_NO_RIGHTS;
  }

  taosSendSimpleRsp(pConn->thandle, TSDB_MSG_TYPE_QUERY_GATE_RSP, code);

  return 0;
}
