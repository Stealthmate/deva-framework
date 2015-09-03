#ifndef DEVA_FRAMEWORK_MATH_CONFIG_H
#define DEVA_FRAMEWORK_MATH_CONFIG_H

#include "../Config.hpp"

#ifdef _MSC_VER
	#ifdef DEVA_BUILD_MATH
		#ifdef DEVA_BUILD_SHARED
			#define DEVA_MATH_API __declspec(dllexport)
		#else
			#define DEVA_MATH_API __declspec(dllimport)
		#endif
	#else
		#define DEVA_MATH_API
	#endif
#else
	#define DEVA_MATH_API	
#endif

namespace DevaFramework
{
	const float EPS = 1.0E-10f;
	const double M_PI = 3.1415;
}

#endif //DEVA_FRAMEWORK_MATH_CONFIG_H