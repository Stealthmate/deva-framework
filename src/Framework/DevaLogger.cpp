#include "DevaLogger.hpp"

#include "NumberFormatter.hpp"

#include <iostream>

namespace
{

	const std::string STAMP_MESSAGE = "[Deva Framework]: Message: ";
	const std::string STAMP_WARNING = "[Deva Framework]: Warning: ";
	const std::string STAMP_ERROR = "[Deva Framework]: Error: ";
	const std::string STAMP_FATAL_ERROR = "[Deva Framework]: Fatal Error: ";

	using namespace DevaFramework;
}

const DevaLogger DevaLogger::log = DevaLogger(STAMP_MESSAGE, DevaLogger::LogLevel::LOG_MESSAGE, true);
const DevaLogger DevaLogger::warn = DevaLogger(STAMP_WARNING, DevaLogger::LogLevel::LOG_WARNING, true);
const DevaLogger DevaLogger::err = DevaLogger(STAMP_ERROR, DevaLogger::LogLevel::LOG_ERROR, true);

DevaLogger::DevaLogger(const std::string &stampstr, LogLevel loglvl, bool enabled) : Logger(stampstr, enabled), loglvl(loglvl) {}

const Logger& DevaLogger::print(const std::string &msg) const
{
	if (!enabled) return *this;

	switch (this->loglvl)
	{
	case DevaLogger::LogLevel::LOG_MESSAGE:
	{
		std::cout << msg;
	}break;
	case DevaLogger::LogLevel::LOG_WARNING:
	case DevaLogger::LogLevel::LOG_ERROR:
	{
		std::cerr << msg;
	}
	}
	return *this;
}

#pragma message("NEED TO FIX THIS FUNCTION -> DevaLogger:46")

template<typename T>
std::string formatNumberIfNeeded(T num, DevaLogger::NumberFormat format)
{
	switch (format)
	{
	case DevaLogger::NumberFormat::BINARY:
		return NumberFormatter::toBinary((uint64_t)num);
		break;
	case DevaLogger::NumberFormat::HEX:
		return NumberFormatter::toHex((uint64_t)num);
		break;
	case DevaLogger::NumberFormat::PLAIN:
	default:
		return strm(num);
	}
}

const Logger& DevaLogger::operator<<(const std::string &msg) const { return this->print(msg); }
const Logger& DevaLogger::operator<<(const char *msg) const { return this->print(std::string(msg)); }
const Logger& DevaLogger::operator<<(byte_t msg) const {return print(formatNumberIfNeeded(msg, this->numformat)); }
const Logger& DevaLogger::operator<<(signed short msg) const { return print(formatNumberIfNeeded(msg, this->numformat)); }
const Logger& DevaLogger::operator<<(unsigned short msg) const { return print(formatNumberIfNeeded(msg, this->numformat)); }
const Logger& DevaLogger::operator<<(signed int msg) const { return print(formatNumberIfNeeded(msg, this->numformat)); }
const Logger& DevaLogger::operator<<(unsigned int msg) const { return print(formatNumberIfNeeded(msg, this->numformat)); }
const Logger& DevaLogger::operator<<(signed long long msg) const { return print(formatNumberIfNeeded(msg, this->numformat)); }
const Logger& DevaLogger::operator<<(unsigned long long msg) const { return print(formatNumberIfNeeded(msg, this->numformat)); }
const Logger& DevaLogger::operator<<(bool msg) const { return print(formatNumberIfNeeded(msg, this->numformat)); }


const Logger& DevaLogger::operator<<(DevaLogger::NumberFormat numformat) const
{
	this->numformat = numformat;
	return *this;
}