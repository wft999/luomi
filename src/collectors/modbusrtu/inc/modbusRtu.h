#ifndef LUOMI_MODBUSRTU_H
#define LUOMI_MODBUSRTU_H

#ifdef __cplusplus
extern "C" {
#endif



void modbusRtuCleanUpSystem();
int  modbusRtuInitSystem();
int modbusRtuStartSystem();
int modbusRtuStopSystem();

#ifdef __cplusplus
}
#endif

#endif
