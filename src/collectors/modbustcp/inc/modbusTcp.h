#ifndef LUOMI_MODBUSTCP_H
#define LUOMI_MODBUSTCP_H

#ifdef __cplusplus
extern "C" {
#endif



void modbusTcpCleanUpSystem();
int  modbusTcpInitSystem();
int modbusTcpStartSystem();
int modbusTcpStopSystem();

#ifdef __cplusplus
}
#endif

#endif
