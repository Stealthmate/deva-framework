#ifndef DEVA_FRAMEWORK_UTIL_TIME_HPP
#define DEVA_FRAMEWORK_UTIL_TIME_HPP

#include "Config.hpp"

namespace DevaFramework {

	enum TimeUnit {
		NANOSECONDS,
		MICROSECONDS,
		MILLISECONDS,
		SECONDS
	};

	DEVA_FRAMEWORK_API size_t getSystemTime(TimeUnit unit = MILLISECONDS);


}

#endif // DEVA_FRAMEWORK_UTIL_TIME_HPP