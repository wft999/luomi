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

#ifndef TDENGINE_MGMT_LMDB_H
#define TDENGINE_MGMT_LMDB_H

#ifdef __cplusplus
extern "C" {
#endif

#include <errno.h>

#include "sdb.h"
#include "tglobalcfg.h"
#include "thash.h"
#include "tidpool.h"
#include "tlog.h"
#include "tmempool.h"
#include "trpc.h"
#include "tsdb.h"
#include "tsdb.h"
#include "tskiplist.h"
#include "tsocket.h"
#include "ttime.h"
#include "ttimer.h"
#include "tutil.h"

#define TSDB_GATE_ID_LEN		32
#define TSDB_GATE_SETTING_LEN   TSDB_MAX_SQL_LEN - 100
#define TSDB_GATE_MAX_NUM		1000

typedef struct _gate_obj {
  char          	name[TSDB_GATE_ID_LEN];
  char              setting[TSDB_GATE_SETTING_LEN + 1];
  char              updateEnd[1];
} SGateObj;

typedef struct {
	char          	name[TSDB_GATE_ID_LEN];
	char    		setting[TSDB_GATE_SETTING_LEN + 1];
} SCreateGateMsg, SAlterGateMsg;

extern char tsGateName[];
extern int tsGateUpdateSize;

#ifdef __cplusplus
}
#endif

#endif  // TDENGINE_MGMT_H
