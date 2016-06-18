#include "MatrixFactory.hpp"
#include <cmath>

using namespace DevaFramework;

mat4 DevaFramework::rotate(float angle, vec3 axis)
{
	vec3 axis_normal = axis.normal();

	float c = (float)std::cos((double)angle);
	float s = (float)std::sin((double)angle);
	float x = axis_normal[0];
	float y = axis_normal[1];
	float z = axis_normal[2];
	return mat4
	{ 
		vec4{ c + ((x*x)*(1-c)),     (x*y*(1 - c)) - (z*s), (x*z*(1 - c)) + (y*s), 0}, 
		vec4{ (x*y*(1 - c)) + (z*s), c + ((y*y)*(1 - c)),     (y*z*(1 - c)) - (x*s), 0},
		vec4{ (x*z*(1 - c)) - (y*s), (z*y*(1 - c)) + (x*s), c + ((z*z)*(1 - c)), 0},
		vec4{0, 0, 0, 1}
	};
}
/*
mat4 DevaFramework::rotate(const Quaternion &q)
{

}
*/
mat4 DevaFramework::scale(vec3 scale_vector)
{
	return{ vec4{scale_vector[0], 0, 0, 0 }, vec4{0, scale_vector[1], 0, 0}, vec4{0, 0, scale_vector[2], 0}, vec4{0, 0, 0, 1} };
};

mat4 DevaFramework::translate(vec3 translation_vector)
{
	return{ vec4{1, 0, 0, 0}, vec4{0, 1, 0, 0}, vec4{0, 0, 1, 0}, vec4{translation_vector[0], translation_vector[1], translation_vector[2], 1} };
}