#include "Logger.hpp"
#include <chrono>
#include <ctime>
#include <iostream>
#include <cstdlib>

using namespace DevaFramework;


#include "Logger-format.inl"

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


const std::string Logger::endl = "\n";

Logger::Logger(const std::string &stampstr) : stampstr(stampstr) {}

const Logger& Logger::println(const std::string &msg) const { return *this << stampstr << msg << endl; }