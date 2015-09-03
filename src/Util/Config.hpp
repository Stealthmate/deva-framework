#ifndef DEVA_FRAMEWORK_UTIL_CONFIG_H
#define DEVA_FRAMEWORK_UTIL_CONFIG_H

#include "../Config.hpp"

#ifdef _MSC_VER
	#ifdef DEVA_BUILD_UTIL
		#ifdef DEVA_BUILD_SHARED
			#define DEVA_UTIL_API __declspec(dllexport)
		#else
			#define DEVA_UTIL_API __declspec(dllimport)
		#endif
	#else
		#define DEVA_UTIL_API
	#endif
#endif

#endif // DEVA_FRAMEWORK_GRAPHICS_CONFIG_H
