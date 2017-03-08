#ifndef DEVA_FRAMEWORK_CORE_LOGGER_HPP
#define DEVA_FRAMEWORK_CORE_LOGGER_HPP

#include "Config.hpp"

#include <string>
#include <fmt\format.h>
namespace DevaFramework
{

	template <typename... Args>
	std::string strformat(const std::string &str, const Args & ... args) {
		return fmt::format(str, args...);
	}

	class Logger
	{
	protected:
		std::string stampstr;
		bool enabled;
	public:

		DEVA_FRAMEWORK_API static const std::string endl;

		DEVA_FRAMEWORK_API Logger(const std::string &stampstr);

		DEVA_FRAMEWORK_API virtual const Logger& println(const std::string &msg) const;


		inline virtual const Logger& operator<<(const std::string &msg) const { return enabled ? this->print(msg) : *this; }
		inline virtual const Logger& operator<<(const char *msg) const { return enabled ? this->print(std::string(msg)) : *this; }

		/*
		To the future Me (or whoever reads this):
		Please do not blame me for using defines. I'm trying as hard as I can to follow the DRY principle.
		Thank you.
		*/
#define INSERTION_FOR_TYPE(TYPE) inline virtual const Logger& operator<<(TYPE msg) const { return enabled ? this->print(strm(msg)) : *this; }
		INSERTION_FOR_TYPE(byte_t);
		INSERTION_FOR_TYPE(signed short);
		INSERTION_FOR_TYPE(unsigned short);
		INSERTION_FOR_TYPE(signed int);
		INSERTION_FOR_TYPE(unsigned int);
		INSERTION_FOR_TYPE(signed long long);
		INSERTION_FOR_TYPE(unsigned long long);
		INSERTION_FOR_TYPE(bool);
#undef INSERTION_FOR_TYPE


		DEVA_FRAMEWORK_API void toggle(bool enabled);
		DEVA_FRAMEWORK_API bool isEnabled() const;

	protected:
		DEVA_FRAMEWORK_API virtual const Logger& print(const std::string &msg) const = 0;
	};
}

#endif // DEVA_FRAMEWORK_CORE_LOGGER_HPP
