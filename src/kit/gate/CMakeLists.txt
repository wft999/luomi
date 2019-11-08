CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(TDengine)

AUX_SOURCE_DIRECTORY(./src SRC)
INCLUDE_DIRECTORIES(inc ${TD_ROOT_DIR}/src/inc ${TD_OS_DIR}/inc ${TD_ROOT_DIR}/src/collectors/modbustcp/inc  ${TD_ROOT_DIR}/src/collectors/modbusrtu/inc)

IF (TD_LINUX)
	LIST(REMOVE_ITEM SRC ./src/gateWindows.c)
ELSEIF (TD_WINDOWS)
	INCLUDE_DIRECTORIES(${TD_ROOT_DIR}/deps/pthread)  
	LIST(REMOVE_ITEM SRC ./src/gateLinux.c)
ENDIF ()

ADD_EXECUTABLE(lm_gate ${SRC})
TARGET_LINK_LIBRARIES(lm_gate taos_static modbustcp modbusrtu tutil pthread)
