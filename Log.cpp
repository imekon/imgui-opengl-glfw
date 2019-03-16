#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdarg.h>

#include "Log.h"

using namespace std;

string Log::message;

void Log::log(const char *format, ...)
{
	va_list args;
	va_start(args, format);
	char buffer[1024];
	vsprintf(buffer, format, args);
	message = buffer;
	va_end(args);
}