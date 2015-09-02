#ifndef DEVA_FRAMEWORK_MATH_VECTOR_H
#define DEVA_FRAMEWORK_MATH_VECTOR_H

#include "BaseVector.hpp"

namespace DevaFramework
{
	typedef BaseVector<float, 2> vec2;
	typedef BaseVector<float, 3> vec3;
	typedef BaseVector<float, 4> vec4;

	typedef BaseVector<double, 2> dvec2;
	typedef BaseVector<double, 3> dvec3;
	typedef BaseVector<double, 4> dvec4;

	typedef BaseVector<unsigned int, 2> uvec2;
	typedef BaseVector<unsigned int, 3> uvec3;
	typedef BaseVector<unsigned int, 4> uvec4;

	typedef BaseVector<int, 2> ivec2;
	typedef BaseVector<int, 3> ivec3;
	typedef BaseVector<int, 4> ivec4;
}

#endif //DEVA_FRAMEWORK_MATH_VECTOR_H