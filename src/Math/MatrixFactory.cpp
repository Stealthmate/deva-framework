#include "MatrixFactory.hpp"
#include <cmath>

using namespace DevaFramework;

mat4 DevaFramework::rotate(float angle, vec3 axis)
{
	vec3 axis_normal = axis.normal();
	return mat4
	{ 
		vec4{cos(angle), 0, sin(angle), 0}, 
		vec4{0, 1, 0, 0}, 
		vec4{-sin(angle), 0, cos(angle), 0}, 
		vec4{0, 0, 0, 1}
	};
}

mat4 DevaFramework::scale(vec3 scale_vector)
{
	return{ vec4{scale_vector[0], 0, 0, 0 }, vec4{0, scale_vector[1], 0, 0}, vec4{0, 0, scale_vector[2], 0}, vec4{0, 0, 0, 1} };
};

mat4 DevaFramework::translate(vec3 translation_vector)
{
	return{ vec4{1, 0, 0, 0}, vec4{0, 1, 0, 0}, vec4{0, 0, 1, 0}, vec4{translation_vector[0], translation_vector[1], translation_vector[2], 1} };
}