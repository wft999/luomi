#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#include "os.h"
#include "tscUtil.h"
#include "tsclient.h"
#include "tsql.h"
#include "ttime.h"
#include "lmdb.h"
#include "tutil.h"

extern int (*tscBuildMsg[TSDB_SQL_MAX])(SSqlObj *pSql);
extern int (*tscProcessMsgRsp[TSDB_SQL_MAX])(SSqlObj *pSql);
void setErrMsg(SSqlCmd* pCmd, const char* pzErrMsg) {
  strncpy(pCmd->payload, pzErrMsg, pCmd->allocSize);
  pCmd->payload[pCmd->allocSize - 1] = 0;
}


int tscBuildCreateGateMsg(SSqlObj *pSql) {
  SCreateGateMsg *pCreateMsg;
  char *          pMsg, *pStart;
  int             msgLen = 0;

  SSqlCmd *pCmd = &pSql->cmd;
  STscObj *pObj = pSql->pTscObj;
  pMsg = pCmd->payload + tsRpcHeadSize;
  pStart = pMsg;

  SMgmtHead *pMgmt = (SMgmtHead *)pMsg;
  strcpy(pMgmt->db, pObj->db);
/*  pMsg += sizeof(SMgmtHead);

  pCreateMsg = (SCreateGateMsg *)pMsg;
  strcpy(pCreateMsg->name, pCmd->name);
  strcpy(pCreateMsg->setting, pCmd->payload);
  pMsg += strlen(pCreateMsg->name) + strlen(pCreateMsg->setting);

  msgLen = pMsg - pStart;
  pCmd->payloadLen = msgLen;

*/
  pCmd->msgType = TSDB_MSG_TYPE_CREATE_GATE;

  return msgLen;
}

int tscBuildQueryGateMsg(SSqlObj *pSql) {
  SCreateGateMsg *pCreateMsg;
  char *          pMsg, *pStart;
  int             msgLen = 0;

  SSqlCmd *pCmd = &pSql->cmd;
  STscObj *pObj = pSql->pTscObj;
  pMsg = pCmd->payload + tsRpcHeadSize;
  pStart = pMsg;

  SMgmtHead *pMgmt = (SMgmtHead *)pMsg;
  strcpy(pMgmt->db, pObj->db);
  pMsg += sizeof(SMgmtHead);

  strcpy(pMsg, pCmd->name);
  pMsg += strlen(pCmd->name)+1;

  msgLen = pMsg - pStart;
  pCmd->payloadLen = msgLen;
  pCmd->msgType = TSDB_MSG_TYPE_QUERY_GATE;

  return msgLen;
}

int tscBuildUpdateGateMsg(SSqlObj *pSql) {
  SCreateGateMsg *pCreateMsg;
  char *          pMsg, *pStart;
  int             msgLen = 0;

  SSqlCmd *pCmd = &pSql->cmd;
  STscObj *pObj = pSql->pTscObj;
  pMsg = pCmd->payload + tsRpcHeadSize;
  pStart = pMsg;

  SMgmtHead *pMgmt = (SMgmtHead *)pMsg;
  strcpy(pMgmt->db, pObj->db);
  pMsg += sizeof(SMgmtHead);

  pCreateMsg = (SCreateGateMsg *)pMsg;
  strcpy(pCreateMsg->name, pCmd->name);
  strcpy(pCreateMsg->setting, pCmd->payload);
  pMsg += strlen(pCreateMsg->name) + strlen(pCreateMsg->setting);

  msgLen = pMsg - pStart;
  pCmd->payloadLen = msgLen;
  pCmd->msgType = TSDB_MSG_TYPE_UPDATE_GATE;

  return msgLen;
}

int tscBuildDeleteGateMsg(SSqlObj *pSql) {
  SCreateGateMsg *pCreateMsg;
  char *          pMsg, *pStart;
  int             msgLen = 0;

  SSqlCmd *pCmd = &pSql->cmd;
  STscObj *pObj = pSql->pTscObj;
  pMsg = pCmd->payload + tsRpcHeadSize;
  pStart = pMsg;

  SMgmtHead *pMgmt = (SMgmtHead *)pMsg;
  strcpy(pMgmt->db, pObj->db);
  pMsg += sizeof(SMgmtHead);

  strcpy(pMsg, pCmd->name);
  pMsg += strlen(pCmd->name)+1;

  msgLen = pMsg - pStart;
  pCmd->payloadLen = msgLen;
  pCmd->msgType = TSDB_MSG_TYPE_DELETE_GATE;

  return msgLen;
}

int tscProcessQueryGateRsp(SSqlObj *pSql){

	return 0;
}

void lmcInitMsgs() {

  tscBuildMsg[TSDB_SQL_CREATE_GATE] = tscBuildCreateGateMsg;
  tscBuildMsg[TSDB_SQL_QUERY_GATE] = tscBuildQueryGateMsg;
  tscBuildMsg[TSDB_SQL_UPDATE_GATE] = tscBuildUpdateGateMsg;
  tscBuildMsg[TSDB_SQL_DELETE_GATE] = tscBuildDeleteGateMsg;
  tscProcessMsgRsp[TSDB_SQL_QUERY_GATE] = tscProcessQueryGateRsp;
}

int32_t setCreateGateInfo(SSqlObj* pSql, struct SSqlInfo* pInfo) {

	int32_t ret = TSDB_CODE_SUCCESS;

	SCreateGateMsg *pCreateMsg;
	char *          pMsg, *pStart;
	int             msgLen = 0;

	SSqlCmd *pCmd = &pSql->cmd;
	STscObj *pObj = pSql->pTscObj;
	pMsg = pCmd->payload + tsRpcHeadSize;
	pStart = pMsg;

	SMgmtHead *pMgmt = (SMgmtHead *)pMsg;
	strcpy(pMgmt->db, pObj->db);
	pMsg += sizeof(SMgmtHead);

	pCreateMsg = (SCreateGateMsg *)pMsg;

	pCmd->command = TSDB_SQL_CREATE_GATE;
	SSQLToken* pToken = &(pInfo->pDCLInfo->a[0]);
	if (pToken->n > TSDB_GATE_ID_LEN) {
		return TSDB_CODE_INVALID_SQL;
	}
	strncpy(pCreateMsg->name, pToken->z, pToken->n);

	SSQLToken* settingToken = &pInfo->pDCLInfo->a[1];
	strncpy(pCreateMsg->setting, settingToken->z, settingToken->n);

	pMsg += sizeof(pCreateMsg->name) + strlen(pCreateMsg->setting)+1;

	msgLen = pMsg - pStart;
	pCmd->payloadLen = msgLen;

	return ret;
}

int32_t setQueryGateInfo(SSqlObj* pSql, struct SSqlInfo* pInfo){
	SSqlCmd* pCmd = &pSql->cmd;
	int32_t ret = TSDB_CODE_SUCCESS;

	pCmd->command = TSDB_SQL_QUERY_GATE;
	SSQLToken* pToken = &(pInfo->pDCLInfo->a[0]);
	if (pToken->n > TSDB_GATE_ID_LEN) {
		return TSDB_CODE_INVALID_SQL;
	}

	strncpy(pCmd->name, pToken->z, pToken->n);

	return ret;
}

int32_t setUpdateGateInfo(SSqlObj* pSql, struct SSqlInfo* pInfo){
	SSqlCmd* pCmd = &pSql->cmd;
	int32_t ret = TSDB_CODE_SUCCESS;

	pCmd->command = TSDB_SQL_UPDATE_GATE;
	SSQLToken* pToken = &(pInfo->pDCLInfo->a[0]);
	if (pToken->n > TSDB_GATE_ID_LEN) {
		return TSDB_CODE_INVALID_SQL;
	}

	strncpy(pCmd->name, pToken->z, pToken->n);
	SSQLToken* settingToken = &pInfo->pDCLInfo->a[1];
	strncpy(pCmd->payload, settingToken->z, settingToken->n);
	pCmd->payloadLen = strlen(pCmd->payload);

	return ret;
}

int32_t setDeleteGateInfo(SSqlObj* pSql, struct SSqlInfo* pInfo){
	SSqlCmd* pCmd = &pSql->cmd;
	int32_t ret = TSDB_CODE_SUCCESS;

	pCmd->command = TSDB_SQL_DELETE_GATE;
	SSQLToken* pToken = &(pInfo->pDCLInfo->a[0]);
	if (pToken->n > TSDB_GATE_ID_LEN) {
		return TSDB_CODE_INVALID_SQL;
	}

	strncpy(pCmd->name, pToken->z, pToken->n);

	return ret;
}
