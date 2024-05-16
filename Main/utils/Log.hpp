#pragma once

void Info(const char *fmt, ...);
void InfoF(const char* file, const char *fmt, ...);
void Error(const char *fmt, ...);
void ErrorF(const char* file, const char *fmt, ...);
void _Debug(const char *fmt, const char *filename, int line, ...);
void _DebugF(const char *file, const char *fmt, const char *filename, int line, ...);

void WriteConsole(const char* level_fmt, ...);
void WriteFile(const char *level_fmt, const char *file, ...);

#define Debug(fmt, args...) _Debug(fmt, __BASE_FILE__, __LINE__, ##args)
#define DebugF(file, fmt, args...) _DebugF(file, fmt, __BASE_FILE__, __LINE__, ##args)