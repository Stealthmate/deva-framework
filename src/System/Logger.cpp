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
//

Logger::func_LogCallback Logger::log_func = [](const std::string &msg, Logger::LogLevel l)
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
};

void Logger::log(const std::string &msg, LogLevel l)
{
	log_func(msg, l);
}