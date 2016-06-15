#include "DevaLogger.hpp"

#include <iostream>

namespace
{

	const std::string STAMP_MESSAGE = "[Deva Framework]: Message: ";
	const std::string STAMP_WARNING = "[Deva Framework]: Warning: ";
	const std::string STAMP_ERROR = "[Deva Framework]: Error: ";
	const std::string STAMP_FATAL_ERROR = "[Deva Framework]: Fatal Error: ";

	using namespace DevaFramework;


}

const DevaLogger DevaLogger::log = DevaLogger(STAMP_MESSAGE, DevaLogger::LogLevel::LOG_MESSAGE);
const DevaLogger DevaLogger::warn = DevaLogger(STAMP_WARNING, DevaLogger::LogLevel::LOG_WARNING);
const DevaLogger DevaLogger::err = DevaLogger(STAMP_ERROR, DevaLogger::LogLevel::LOG_ERROR);

DevaLogger::DevaLogger(const std::string &stampstr, LogLevel loglvl) : Logger(stampstr), loglvl(loglvl) {}

const Logger& DevaLogger::print(const std::string &msg) const
{
	switch (this->loglvl)
	{
	case DevaLogger::LogLevel::LOG_MESSAGE:
	{
		std::cout << stampstr << msg;
	}break;
	case DevaLogger::LogLevel::LOG_WARNING:
	case DevaLogger::LogLevel::LOG_ERROR:
	{
		std::cerr << stampstr << msg;
	}
	}
	return *this;
}

const Logger& DevaLogger::operator<<(const std::string &msg) const { return this->print(msg); }
const Logger& DevaLogger::operator<<(signed char msg) const 
{
	std::string str = strm(msg);
	if (format_numbers) str += " char;";
	return print(str);
}
const Logger& DevaLogger::operator<<(unsigned char msg) const
{
	std::string str = strm(msg);
	if (format_numbers) str += " uchar;";
	return print(str);
}
const Logger& DevaLogger::operator<<(signed short msg) const
{
	std::string str = strm(msg);
	if (format_numbers) str += " short;";
	return print(str);
}
const Logger& DevaLogger::operator<<(unsigned short msg) const
{
	std::string str = strm(msg);
	if (format_numbers) str += " ushort;";
	return print(str);
}
const Logger& DevaLogger::operator<<(signed int msg) const
{
	std::string str = strm(msg);
	if (format_numbers) str += " int;";
	return print(str);
}
const Logger& DevaLogger::operator<<(unsigned int msg) const
{
	std::string str = strm(msg);
	if (format_numbers) str += " uint;";
	return print(str);
}
const Logger& DevaLogger::operator<<(signed long long msg) const
{
	std::string str = strm(msg);
	if (format_numbers) str += " long;";
	return print(str);
}
const Logger& DevaLogger::operator<<(unsigned long long msg) const
{
	std::string str = strm(msg);
	if (format_numbers) str += " ulong;";
	return print(str);
}
const Logger& DevaLogger::operator<<(bool msg) const
{
	std::string str = strm(msg);
	if (format_numbers) str += " bool;";
	return print(str);
}