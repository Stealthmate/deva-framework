#ifndef DEVA_ERROR_ERRORHANDLER_H
#define DEVA_ERROR_ERRORHANDLER_H

#include "Config.hpp"

#include <string>

namespace DevaFramework
{


class Logger
{
public:
	enum LogLevel
	{
		MESSAGE = 0,
		WARNING = 1,
		ERROR = 2,
		FATAL_ERROR = 3
	};
	typedef void(*func_LogCallback)(const std::string &msg, LogLevel l);

private:

	static func_LogCallback log_func;

public:

    static DEVA_API void log(const std::string &msg, LogLevel l = LogLevel::MESSAGE);
};

}

#endif // DEVA_ERROR_ERRORHANDLER_H
