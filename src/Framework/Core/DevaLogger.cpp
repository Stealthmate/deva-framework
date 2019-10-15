#include "DevaLogger.hpp"
#include "TypeInfo.hpp"
#include <iostream>
#include <unordered_map>

using namespace DevaFramework;

namespace
{
	std::unordered_map<DevaLogger::LogLevel, std::string> STAMPS = {
		{ DevaLogger::LogLevel::UNSPECIFIED, "Log: " },
		{ DevaLogger::LogLevel::VERBOSE, "Verbose: " },
		{ DevaLogger::LogLevel::DEBUG, "Debug: " },
		{ DevaLogger::LogLevel::INFO, "Info: " },
		{ DevaLogger::LogLevel::WARN, "Warning: " },
		{ DevaLogger::LogLevel::ERR, "Error: " },
		{ DevaLogger::LogLevel::WTF, "WTF: " }
	};

}

DevaLogger DevaFramework::LOG = DevaLogger("[Log] ");

DevaLogger::DevaLogger(const std::string &stampstr) : Logger(stampstr) {
	for (int i = 0;i < N_LOG_LEVELS;i++) {
		loglvlstates[i] = true;
	}
}

const Logger& DevaLogger::print(const std::string &msg) const
{
	printStamped(msg, UNSPECIFIED, false, true);
	return *this;
}

#pragma message("NEED TO FIX THIS FUNCTION -> DevaLogger:46")

void DevaLogger::printStamped(const std::string &msg, LogLevel lvl, bool newline, bool omitStamp) const {
	std::string priostamp = omitStamp ? "" : stamp() + STAMPS.find(lvl)->second;
	bool shouldPrint = loglvlstates[lvl];
	if (shouldPrint) {
		if (lvl > INFO)
			std::cerr << priostamp << msg;
		else
			std::cout << priostamp << msg;
		if (newline) std::cout << std::endl;
	}
}

void DevaLogger::setPrio(LogLevel lvl) {
	int i = 0;
	for (i = 0;i < lvl;i++) {
		loglvlstates[i] = false;
	}
	for (;i < N_LOG_LEVELS;i++) {
		loglvlstates[i] = true;
	}
}