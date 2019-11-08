/**
 * Copyright (c) 2018 wangky
 * export LOG_LEVEL = debug/info/warn/error
 * export LOG_FILE = 1/save log record to home/log.txt
 */

#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdarg.h>

#define LOG_VERSION "0.1.0"

#ifdef _MSC_VER
#define strcasecmp stricmp
#endif
#define __MODULE__ "Modbus" //模块名称，需要根据自己的模块取名!!!

typedef void (*log_LockFn)(void *udata, int lock);

//export LOG_LEVEL="INFO"
enum { LOG_DEBUG,LOG_INFO, LOG_WARN, LOG_ERROR } ;

#define LOGDEBUG(...) log_log(LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define LOGINFO(...)  log_log(LOG_INFO,   __FILE__, __LINE__, __VA_ARGS__)
#define LOGWARN(...)  log_log(LOG_WARN,   __FILE__, __LINE__, __VA_ARGS__)
#define LOGERR(...)   log_log(LOG_ERROR,  __FILE__, __LINE__, __VA_ARGS__)

void log_log(int level, const char *file, int line, const char *fmt, ...);
void log_comm(const char* comName, const char* direct, const char *fmt, ...);//direct = Tx or Rx
void log_comm2(const char* comName, const char* direct, const char *fmt, ...);//direct = Tx or Rx
void log_comm3(const char* comName, const char* direct, const char *fmt, ...);//direct = Tx or Rx
#endif
