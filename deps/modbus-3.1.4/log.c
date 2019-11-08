#include "../modbus-3.1.4/log.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

//#ifndef WIN32
//#define LOG_USE_COLOR
//#endif

static const char *level_names[] = { "DEBUG", "INFO", "WARN", "ERROR" };

static const char *level_colors[] = { "\x1b[36m", "\x1b[32m", "\x1b[33m",
		"\x1b[31m" };

FILE* log_get_fp() {
	static int isLog = -1; //enable log file
	static FILE *log_fp = NULL;
	if (isLog == -1) {
		const char * isLogFile = getenv("LOG_FILE");
		if (isLogFile != NULL) {
			log_fp = fopen("/home/log.txt", "a+");
			isLog = 1;
			return log_fp;
		} else
			isLog = 0;
	}
	return log_fp;
}

const int log_get_level() {
	static int level = -1;
	if (level == -1) {
		const char * clevel = getenv("LOG_LEVEL");
		if (clevel == NULL)
			level = LOG_DEBUG;
		else {
			if (!strcasecmp(clevel, "INFO"))
				level = LOG_INFO;
			else if (!strcasecmp(clevel, "WARN"))
				level = LOG_WARN;
			else if (!strcasecmp(clevel, "ERROR"))
				level = LOG_ERROR;
			else
				level = LOG_DEBUG;
		}
	}
	return level;
}

const int showColor() {
	static int color = -1;
#ifdef WIN32
	color = 0;
	return color;
#endif
	if (color == -1) {
		const char* col = getenv("LOG_COLOR");
		if (col == NULL)
			color = 0;
		else
			color = 1;
	}
	return color;
}
void log_log(int level, const char *file, int line, const char *fmt, ...) {

	int current_level = log_get_level();
	if (level < current_level) {
		return;
	}

	/* Get current time */
	time_t t = time(NULL);
	struct tm *lt = localtime(&t);

	/* Log to stdout */
	va_list args;
	char buf[16];
	buf[strftime(buf, sizeof(buf), "%H:%M:%S", lt)] = '\0';

	int color = showColor();
	if (color == 1)
		fprintf(stdout, "[%s %s%-5s\x1b[0m \x1b[90m%s:%s:%d\x1b[0m] ", buf,
				level_colors[level], level_names[level], __MODULE__, file, line);
	else
		fprintf(stdout, "[%-5s %s %s:%s:%d] ", buf, level_names[level],
				__MODULE__, file, line);

	va_start(args, fmt);
	vfprintf(stdout, fmt, args);
	va_end(args);
	fprintf(stdout, "\n");
	fflush(stdout);

	/* Log to file */
	FILE * logfile = log_get_fp();
	if (logfile) {
		va_list args;
		char buf[32];
		buf[strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", lt)] = '\0';
		fprintf(logfile, "[%-5s %s %s:%s:%d] ", buf, level_names[level],
				__MODULE__, file, line);
		va_start(args, fmt);
		vfprintf(logfile, fmt, args);
		va_end(args);
		fprintf(logfile, "\n");
		fflush(logfile);
	}
}

void log_comm(const char* comName, const char* direct, const char *fmt, ...) {
	setbuf(stdout, NULL);

	fprintf(stdout, "%s %s: ", comName, direct);
	va_list args;
	va_start(args, fmt);
	vfprintf(stdout, fmt, args);
	va_end(args);
	fprintf(stdout, "\n");
	fflush(stdout);
}

void log_comm2(const char* comName, const char* direct, const char *fmt, ...) {
	setbuf(stdout, NULL);

	fprintf(stdout, "%s %s: ", comName, direct);
	va_list args;
	va_start(args, fmt);
	vfprintf(stdout, fmt, args);
	va_end(args);
//	fprintf(stdout, "\n");
	fflush(stdout);
}

void log_comm3(const char* comName, const char* direct, const char *fmt, ...) {
	setbuf(stdout, NULL);
	time_t t = time(NULL);
	struct tm *lt = localtime(&t);
	char buf[32];
	buf[strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", lt)] = '\0';

	fprintf(stdout, "%s %s %s: ", buf, comName, direct);
	va_list args;
	va_start(args, fmt);
	vfprintf(stdout, fmt, args);
	va_end(args);
	fprintf(stdout, "\n");
	fflush(stdout);
}
