#pragma once

void _Info(const char *fmt, ...);
void _InfoF(const char* file, const char *fmt, ...);
void _Error(const char *fmt, ...);
void _ErrorF(const char* file, const char *fmt, ...);
void _Debug(const char *fmt, ...);
void _DebugF(const char *file, const char *fmt, ...);

#define Debug(fmt, args...) _Debug(fmt, ##args)
#define Info(fmt, args...) _Info(fmt, ##args)
#define Error(fmt, args...) _Error(fmt, ##args)
// #define Debug(fmt, args...) _DebugF("debug.log", fmt, ##args)
// #define Info(fmt, args...) _InfoF("info.log", fmt, ##args)
// #define Error(fmt, args...) _ErrorF("error.log", fmt, ##args)