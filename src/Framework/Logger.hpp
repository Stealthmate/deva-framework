#ifndef DEVA_FRAMEWORK_LOGGER_H
#define DEVA_FRAMEWORK_LOGGER_H

#include "Config.hpp"

#include <string>

namespace DevaFramework
{

	class Logger
	{
	protected:
		std::string stampstr;
	public:

		DEVA_FRAMEWORK_API static const std::string endl;

		DEVA_FRAMEWORK_API Logger(const std::string &stampstr);

		DEVA_FRAMEWORK_API virtual const Logger& println(const std::string &msg) const;


		inline virtual const Logger& operator<<(const std::string &msg) const { return this->print(msg); }
		inline virtual const Logger& operator<<(const char *msg) const { return this->print(std::string(msg)); }
		//DEVA_FRAMEWORK_API virtual const Logger& operator<<(const std::string &msg) const;
		/*
		To the future Me (or whoever reads this):
		Please do not blame me for using defines. I'm trying as hard as I can to follow the DRY principle.
		Thank you.
		*/
#define INSERTION_FOR_TYPE(TYPE) inline virtual const Logger& operator<<(TYPE msg) const { return this->print(strm(msg)); }
		INSERTION_FOR_TYPE(byte_t);
		INSERTION_FOR_TYPE(signed short);
		INSERTION_FOR_TYPE(unsigned short);
		INSERTION_FOR_TYPE(signed int);
		INSERTION_FOR_TYPE(unsigned int);
		INSERTION_FOR_TYPE(signed long long);
		INSERTION_FOR_TYPE(unsigned long long);
		INSERTION_FOR_TYPE(bool);
#undef INSERTION_FOR_TYPE

	protected:
		DEVA_FRAMEWORK_API virtual const Logger& print(const std::string &msg) const = 0;
	};

	extern const Logger& __deva_log;
	extern const Logger& __deva_warn;
	extern const Logger& __deva_err;
}

#endif // DEVA_FRAMEWORK_LOGGER_H
