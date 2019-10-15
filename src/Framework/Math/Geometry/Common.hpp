#ifndef DEVA_FRAMEWORK_MATH_GEOMETRY_COMMON_HPP
#define DEVA_FRAMEWORK_MATH_GEOMETRY_COMMON_HPP

#include "Config.hpp"
#include "../Vector.hpp"

namespace DevaFramework {

	DEVA_FRAMEWORK_API float vectorAngle(const vec2 &v1, const vec2 &v2);
	DEVA_FRAMEWORK_API float vectorAngle(const vec3 &v1, const vec3 &v2);
	DEVA_FRAMEWORK_API float vectorAngle(const vec4 &v1, const vec4 &v2);

}

#endif // DEVA_FRAMEWORK_MATH_GEOMETRY_COMMON_HPP