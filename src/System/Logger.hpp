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

	func_LogCallback log_func;

	LogLevel level;



public:

	static DEVA_SYSTEM_API const Logger log;
	static DEVA_SYSTEM_API const Logger warn;
	static DEVA_SYSTEM_API const Logger err;
	static DEVA_SYSTEM_API const Logger assert;

	DEVA_SYSTEM_API Logger(LogLevel level, func_LogCallback f);

	template<typename T>
	const Logger& operator<<(const T &msg) const
	{
		log_func(strm(msg), this->level);
		return *this;
	}
};

}

#endif // DEVA_ERROR_ERRORHANDLER_H
