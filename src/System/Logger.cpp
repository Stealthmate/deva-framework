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

const std::string STAMP_MESSAGE = "[Deva Framework]: Message: ";
const std::string STAMP_WARNING = "[Deva Framework]: Warning: ";
const std::string STAMP_ERROR = "[Deva Framework]: Error: ";
const std::string STAMP_FATAL_ERROR = "[Deva Framework]: Fatal Error: ";



void default_log_func(const std::string &msg, Logger::LogLevel l)
{
	switch (l)
	{
	case Logger::LogLevel::MESSAGE:
	{
		std::cout << msg;
	}break;
	case Logger::LogLevel::WARNING:
	case Logger::LogLevel::ERROR:
	case Logger::LogLevel::FATAL_ERROR:
	{
		std::cerr << msg;
	}
	}
}

DEVA_SYSTEM_API const Logger Logger::log    = Logger(default_log_func, MESSAGE, STAMP_MESSAGE);
DEVA_SYSTEM_API const Logger Logger::warn   = Logger(default_log_func, WARNING, STAMP_WARNING);
DEVA_SYSTEM_API const Logger Logger::err    = Logger(default_log_func, ERROR, STAMP_ERROR);
DEVA_SYSTEM_API const Logger Logger::assert = Logger(default_log_func, FATAL_ERROR, STAMP_FATAL_ERROR);
DEVA_SYSTEM_API const std::string Logger::endl = "\n";

void Logger::println(const std::string &msg, const Logger &out)
{
	out << out.stamp << msg << Logger::endl;
}

Logger::Logger(func_LogCallback f, LogLevel level, const std::string &stamp) 
	: log_func(f), level(level), stamp(stamp) {}

