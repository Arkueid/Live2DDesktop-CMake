#include "Log.hpp"

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <stdarg.h>

void current_time(char *buf)
{
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buf, 80, "%Y-%m-%d %H:%M:%S", timeinfo);
}

void Info(const char *msg)
{
    char buf[80];
    current_time(buf);
    WriteConsole(LOG_INFO_CONSOLE_FORMAT, buf, msg);
}

void Info(const char *msg, const char *file)
{
    char buf[80];
    current_time(buf);
    WriteFile(LOG_INFO_FILE_FORMAT, file, buf, msg);
}

void Error(const char *msg)
{
    char buf[80];
    current_time(buf);
    WriteConsole(LOG_ERROR_CONSOLE_FORMAT, buf, msg);
}

void Error(const char *msg, const char *file)
{
    char buf[80];
    current_time(buf);
    WriteFile(LOG_ERROR_FILE_FORMAT, file, buf, msg);
}

void WriteConsole(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), fmt, args);

    va_end(args);

    printf(buffer);
}

void WriteFile(const char *fmt, const char *file, ...)
{
    std::fstream f;

    f.open(file, std::ios::app);
    
    if (!f.is_open())
    {
        perror("file open error");
        exit(-1);
    }

    va_list args;
    va_start(args, file);

    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), fmt, args);

    f << buffer;

    va_end(args);

    f.close();
}
