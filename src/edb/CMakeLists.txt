CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(LMdatabase)

AUX_SOURCE_DIRECTORY(./src SRC)

IF (TD_LINUX)
			INCLUDE_DIRECTORIES(inc  ${TD_ROOT_DIR}/src/inc ${TD_ROOT_DIR}/src/os/linux/inc ${TD_ROOT_DIR}/deps/zlib-1.2.11/inc ${TD_ROOT_DIR}/deps/zstd-1.4.4/lib)
			
			ADD_LIBRARY(edb ${SRC})
			SET_TARGET_PROPERTIES(edb PROPERTIES CLEAN_DIRECT_OUTPUT 1)
			
			TARGET_LINK_LIBRARIES(edb tutil z)  
ELSEIF (TD_WINDOWS)
		INCLUDE_DIRECTORIES(inc  ${TD_ROOT_DIR}/src/inc ${TD_ROOT_DIR}/src/os/windows/inc ${TD_ROOT_DIR}/deps/pthread ${TD_ROOT_DIR}/deps/zstd-1.4.4/lib)
	

		ADD_LIBRARY(edb_static STATIC ${SRC})
  TARGET_LINK_LIBRARIES(edb_static trpc tutil)
	
		ADD_LIBRARY(edb SHARED ${SRC})
  SET_TARGET_PROPERTIES(edb PROPERTIES LINK_FLAGS /DEF:${TD_ROOT_DIR}/src/edb/src/luomi.def)
  TARGET_LINK_LIBRARIES(edb trpc)
ENDIF ()

 


