#ifndef DEVA_FRAMEWORK_MATH_CONFIG_H
#define DEVA_FRAMEWORK_MATH_CONFIG_H

#include "../Config.hpp"

namespace DevaFramework
{
	const float EPS = 1.0E-10f;
	const double M_PI = std::acos(-1);
	const double TWOPI = 2 * M_PI;

	///Converts degrees to radians
	inline double rad(double deg)
	{
		return M_PI*deg / 180.f;
	}
	///Converts radians to degrees
	inline double deg(double rad)
	{
		return rad*180.f / M_PI;
	}

}

#endif //DEVA_FRAMEWORK_MATH_CONFIG_H
