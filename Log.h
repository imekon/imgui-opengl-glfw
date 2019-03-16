#pragma once

#include <string>

class Log
{
public:
	static void log(const char *format, ...);
	static const char *getMessage() { return message.c_str(); }

private:
	static std::string message;
};

