#pragma once

#include <stdint.h>
#include <string.h>

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"
#elif __GNUC__
#pragma GCC diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"
#endif

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define log_info(format, ...) log_file_(LOG_TYPE_INFO, __LINE__, __FILENAME__, format, ##__VA_ARGS__)

#define log_error(format, ...) log_file_(LOG_TYPE_ERROR, __LINE__, __FILENAME__, format, ##__VA_ARGS__)

#define log_warn(format, ...) log_file_(LOG_TYPE_WARN, __LINE__, __FILENAME__, format, ##__VA_ARGS__)

#define log_debug(format, ...) log_file_(LOG_TYPE_DEBUG, __LINE__, __FILENAME__, format, ##__VA_ARGS__)

#ifdef __clang__
#pragma clang diagnostic pop
#endif

enum log_type {
	LOG_TYPE_INFO,
	LOG_TYPE_ERROR,
	LOG_TYPE_WARN,
	LOG_TYPE_DEBUG
};

void log_file_(enum log_type type, int32_t line, const char* file, const char* format, ...);
