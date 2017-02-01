#ifndef DEVA_FRAMEWORK_MATH_CONFIG_H
#define DEVA_FRAMEWORK_MATH_CONFIG_H

#include "../Config.hpp"

namespace DevaFramework
{
	const float EPS = 1.0E-10f;
	const double M_PI = 3.1415;
	const double TWOPI = 2 * M_PI;

	///Converts degrees to radians
	inline float rad(float deg)
	{
		return static_cast<float>(M_PI*deg / 180.f);
	}
	///Converts radians to degrees
	inline float deg(float rad)
	{
		return static_cast<float>(rad*180.f / M_PI);
	}

}

#endif //DEVA_FRAMEWORK_MATH_CONFIG_H
