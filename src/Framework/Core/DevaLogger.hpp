#ifndef DEVA_FRAMEWORK_CORE_DEVA_LOGGER_HPP
#define DEVA_FRAMEWORK_CORE_DEVA_LOGGER_HPP

#include "Config.hpp"

#include "Logger.hpp"

namespace DevaFramework
{
	class DevaLogger : public Logger
	{

	public:

		static const size_t N_LOG_LEVELS = 6;
		enum LogLevel : uint8_t
		{
			UNSPECIFIED = 0,
			VERBOSE = 1,
			DEBUG = 2,
			INFO = 3,
			WARN = 4,
			ERR = 5,
			WTF = 6
		};

		enum NumberFormat
		{
			PLAIN = 0,
			BINARY = 1,
			HEX = 2
		};

	protected:
		bool loglvlstates[N_LOG_LEVELS];

	public:
		DEVA_FRAMEWORK_API DevaLogger(const std::string &stamp);

		inline std::string stamp() const { return this->stampstr; }

#define MAKE_LOG_FUNCTION(fname, ll) \
	DEVA_FRAMEWORK_API inline virtual void fname(const std::string &msg, bool newline = true) const { printStamped(msg, ll, newline); }

		MAKE_LOG_FUNCTION(v, VERBOSE);
		MAKE_LOG_FUNCTION(d, DEBUG);
		MAKE_LOG_FUNCTION(i, INFO);
		MAKE_LOG_FUNCTION(w, WARN);
		MAKE_LOG_FUNCTION(e, ERR);
		MAKE_LOG_FUNCTION(wtf, WTF);

#undef MAKE_LOG_FUNCTION

		DEVA_FRAMEWORK_API void toggleLevel(LogLevel level);
		DEVA_FRAMEWORK_API void toggleLevel(LogLevel level, bool enable);
		DEVA_FRAMEWORK_API void setPrio(LogLevel level);

		DEVA_FRAMEWORK_API void printStamped(const std::string &msg, LogLevel loglvl, bool newline = false, bool omitStamp = false) const;

	protected:
		DEVA_FRAMEWORK_API virtual const Logger& print(const std::string &msg) const override;
	};

	DEVA_FRAMEWORK_API extern DevaLogger LOG;
}

#endif //DEVA_FRAMEWORK_CORE_DEVA_LOGGER_HPP
