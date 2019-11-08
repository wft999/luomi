#ifndef LUOMI_GATESYSTEM_H
#define LUOMI_GATESYSTEM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

enum _module { GATE_MODBUS_TCP, GATE_MODBUS_RTU, GATE_MOD_MAX };

typedef struct {
  char  *name;
  int  (*initFp)();
  void (*cleanUpFp)();
  int  (*startFp)();
  void (*stopFp)();
  int	enable;
} GModule;

typedef struct {
	int enableModbusTcp;
	int enableModbusRtu;
} GATE_INFO;

extern uint32_t        lmModuleStatus;
extern GModule         lmModule[];
//extern pthread_mutex_t dmutex;

void gateCleanUpSystem();
int  gateInitSystem();
int gateStartSystem();
int gateStopSystem();

#ifdef __cplusplus
}
#endif

#endif
