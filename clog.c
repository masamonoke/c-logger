#include "clog.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <sys/file.h>
#include <stdarg.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

static const char* log_filename = "logs.log";
static bool die_sentenced = false;

static bool write_log(enum log_type type, int32_t line, const char* file, const char* buf, FILE* fp);

// it LOG_FILE not defined log_filename used as sync file
void log_file_(enum log_type type, int32_t line, const char* file, const char* format, ...) { // NOLINT
	FILE* fp;
	va_list args;
	char buf[1024];

#ifdef LOG_SYNC
	fp = fopen(log_filename, "a");
	if (fp) {
		if (flock(fileno(fp), LOCK_EX)) {
			fprintf(stderr, "Failed to open lock file %s\n", log_filename);
			exit(1);
		}

		va_start(args, format);

		if (vsnprintf(buf, sizeof(buf), format, args) < 0 || !write_log(type, line, file, buf, fp)) {
			fprintf(stderr, "Failed to write buffer\n");
			die_sentenced = true;
		}

		va_end(args);

		if (flock(fileno(fp), LOCK_UN)) {
			fprintf(stderr, "Failed to unlock file %s\n", log_filename);
			exit(1);
		}

		if (die_sentenced) {
			fprintf(stderr, "Log writing error\n");
			exit(1);
		}

	} else {
		fprintf(stderr, "Failed to open log file %s\n", log_filename);
		exit(1);
	}


	fclose(fp);
#else
#ifdef LOG_FILE
#undef LOG_FILE
#endif
	va_start(args, format);

	if (vsnprintf(buf, sizeof(buf), format, args) < 0 || !write_log(type, line, file, buf, fp)) {
		fprintf(stderr, "Failed to write buffer\n");
		die_sentenced = true;
	}

	va_end(args);
#endif
}

static bool log(const char* color, const char* log_type, int32_t line, const char* file, const char* buf, FILE* fp, enum log_type type) {
	(void) fp;
	(void) type;

	if (fprintf(stderr, "%s %-5s | %-20s | %-5d |" ANSI_COLOR_RESET ": [%s]\n", color, log_type,  file, line, buf) < 0) {
		return false;
	}
#ifdef LOG_FILE
	if (fprintf(fp, "%-5s | %-20s | %-5d |: [%s]\n", log_type, file, line, buf) < 0) {
		return false;
	}
#endif
	return true;
}

static bool write_log(enum log_type type, int32_t line, const char* file, const char* buf, FILE* fp) { // NOLINT
	bool res;

	res = true;
	switch(type) {
		case LOG_TYPE_INFO:
			res = log(ANSI_COLOR_CYAN, "Info", line, file, buf, fp, type);
			break;
		case LOG_TYPE_ERROR:
			res = log(ANSI_COLOR_RED, "Error", line, file, buf, fp, type);
			break;
		case LOG_TYPE_WARN:
			res = log(ANSI_COLOR_YELLOW, "Warn", line, file, buf, fp, type);
			break;
		case LOG_TYPE_DEBUG:
#ifdef DEBUG
			res = log(ANSI_COLOR_GREEN, "Debug", line, file, buf, fp, type);
#endif
			break;
	}

	return res;
}
