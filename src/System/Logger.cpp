#include "Logger.hpp"
#include <chrono>
#include <ctime>
#include <iostream>
#include <cstdlib>

using namespace DevaFramework;

std::string timestamp()
{
    /*using namespace std::chrono;
    std::string time;
    std::string time_ms = ":";
    auto _now = high_resolution_clock::now();
    auto now = high_resolution_clock::to_time_t(_now);
    auto t = duration_cast<microseconds>(_now.time_since_epoch());
    time = std::ctime(&now);
    auto ms = (t.count()/1000)%1000;
    if(ms<10) time_ms+="0";
    if(ms<100) time_ms += "0";
    time_ms+=strm(ms);
    if(!ErrorHandler::showMS) time_ms = "";
    return std::string("[") + time.substr(11, 8) + time_ms + "] ";*/
	return "";
}

void default_log_func (const std::string &msg, Logger::LogLevel l)
{
	switch (l)
	{
	case Logger::LogLevel::MESSAGE:
	{
		std::cout << "[Deva Framework]: Message: " << msg << std::endl;
	}break;
	case Logger::LogLevel::WARNING:
	{
		std::cerr << "[Deva Framework]: Warning: " << msg << std::endl;
	}break;
	case Logger::LogLevel::ERROR:
	{
		std::cerr << "[Deva Framework]: Error: " << msg << std::endl;
	}break;
	case Logger::LogLevel::FATAL_ERROR:
	{
		std::cerr << "[Deva Framework]: Fatal Error: " << msg << std::endl;
		std::cerr << "[Deva Framework]: Fatal Error: " << msg << std::endl;
		exit(1);
	}
	}
}

DEVA_SYSTEM_API const Logger Logger::log = Logger(Logger::LogLevel::MESSAGE, default_log_func);
DEVA_SYSTEM_API const Logger Logger::warn = Logger(Logger::LogLevel::WARNING, default_log_func);
DEVA_SYSTEM_API const Logger Logger::err = Logger(Logger::LogLevel::ERROR, default_log_func);
DEVA_SYSTEM_API const Logger Logger::assert = Logger(Logger::LogLevel::FATAL_ERROR, default_log_func);

Logger::Logger(LogLevel level, func_LogCallback f) : level(level), log_func(f) {}

/*Logger::func_LogCallback Logger::log_func = [](const std::string &msg, Logger::LogLevel l)
{
	switch (l)
	{
	case MESSAGE :
	{
		std::cout << "[Deva Framework]: Message: " << msg << std::endl;
	}break;
	case WARNING :
	{
		std::cerr << "[Deva Framework]: Warning: " << msg << std::endl;
	}break;
	case ERROR :
	{
		std::cerr << "[Deva Framework]: Error: " << msg << std::endl;
	}break;
	case FATAL_ERROR :
	{
		std::cerr << "[Deva Framework]: Fatal Error: " << msg << std::endl;
		std::cerr << "[Deva Framework]: Fatal Error: " << msg << std::endl;
		exit(1);
	}
	}
};*/

/*const Logger& Logger::operator<<(const std::string &msg) const
{
	log_func(msg, level);
	return *this;
}*/