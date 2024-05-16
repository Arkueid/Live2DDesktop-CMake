#pragma once

#define LOG_INFO_CONSOLE_FORMAT "\033[32m[INFO-%s] %s\033[0m\n"
#define LOG_ERROR_CONSOLE_FORMAT "\033[31m[ERROR-%s] %s\033[0m\n"
#define LOG_INFO_FILE_FORMAT    "[INFO-%s] %s\n"
#define LOG_ERROR_FILE_FORMAT   "[ERROR-%s] %s\n"
#define LOG_INFO_OUTPUT "info.log"
#define LOG_ERROR_OUTPUT "error.log"

#define LOG_DEBUG_CONSOLE_FORMAT "\033[34m[DEBUG] %s:%d: %s\033[0m\n"
#define LOG_DEBUG_FILE_FORMAT "[DEBUG] %s:%d: %s\n"

void Info(const char *msg);
void Info(const char *msg, const char* file);
void Error(const char *msg);
void Error(const char *msg, const char* file);

void WriteConsole(const char *fmt, ...);
void WriteFile(const char *fmt, const char *file, ...);

#define Debug(msg) WriteConsole(LOG_DEBUG_CONSOLE_FORMAT, __FILE__, __LINE__, #msg)
#define Debug2File(msg, file) WriteFile(LOG_DEBUG_FILE_FORMAT, file, __FILE__, __LINE__, msg)
