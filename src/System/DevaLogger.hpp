#ifndef DEVA_FRAMEWORK_SYSTEM_DEVA_LOGGER_H
#define DEVA_FRAMEWORK_SYSTEM_DEVA_LOGGER_H

#include "Config.hpp"

#include "Logger.hpp"

namespace DevaFramework
{
	class DevaLogger : public Logger
	{

	public:
		enum LogLevel
		{
			LOG_MESSAGE = 0,
			LOG_WARNING = 1,
			LOG_ERROR   = 2
		};

		enum NumberFormat
		{
			PLAIN = 0,
			BINARY = 1,
			HEX = 2
		};

	public:
		DEVA_FRAMEWORK_API static const DevaLogger log;
		DEVA_FRAMEWORK_API static const DevaLogger warn;
		DEVA_FRAMEWORK_API static const DevaLogger err;

	protected:
		const LogLevel loglvl;
		mutable NumberFormat numformat;

	public:
		DEVA_FRAMEWORK_API DevaLogger(const std::string &stamp, LogLevel loglvl);

		DEVA_FRAMEWORK_API virtual const Logger& operator<<(const std::string &msg) const;
		DEVA_FRAMEWORK_API virtual const Logger& operator<<(byte_t msg) const;
		DEVA_FRAMEWORK_API virtual const Logger& operator<<(signed short msg) const;
		DEVA_FRAMEWORK_API virtual const Logger& operator<<(unsigned short msg) const;
		DEVA_FRAMEWORK_API virtual const Logger& operator<<(signed int msg) const;
		DEVA_FRAMEWORK_API virtual const Logger& operator<<(unsigned int msg) const;
		DEVA_FRAMEWORK_API virtual const Logger& operator<<(signed long long msg) const;
		DEVA_FRAMEWORK_API virtual const Logger& operator<<(unsigned long long msg) const;
		DEVA_FRAMEWORK_API virtual const Logger& operator<<(bool msg) const;

		DEVA_FRAMEWORK_API virtual const Logger& operator<<(NumberFormat numformat) const final;

		inline virtual std::string stamp() const { return this->stampstr; }

		DEVA_FRAMEWORK_API void setNumberFormat(NumberFormat numformat);

	protected:
		DEVA_FRAMEWORK_API virtual const Logger& print(const std::string &msg) const;

	};
}

#endif //DEVA_FRAMEWORK_SYSTEM_DEVA_LOGGER_H