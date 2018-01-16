#include "MatrixFactory.hpp"
#include "Common.hpp"
#include <cmath>

using namespace DevaFramework;

mat4 Math::rotate(double angle, vec3 axis)
{
	vec3 axis_normal = Math::normal(axis);

	double c = std::cos(angle);
	double s = std::sin(angle);
	float x = axis_normal[0];
	float y = axis_normal[1];
	float z = axis_normal[2];
	return mat4
	{
		vec4{ static_cast<float>(c + ((x*x)*(1 - c))), static_cast<float>((x*y*(1 - c)) - (z*s)), static_cast<float>((x*z*(1 - c)) + (y*s)), 0},
		vec4{ static_cast<float>((x*y*(1 - c)) + (z*s)), static_cast<float>(c + ((y*y)*(1 - c))), static_cast<float>((y*z*(1 - c)) - (x*s)), 0},
		vec4{ static_cast<float>((x*z*(1 - c)) - (y*s)), static_cast<float>((z*y*(1 - c)) + (x*s)), static_cast<float>(c + ((z*z)*(1 - c))), 0},
		vec4{0, 0, 0, 1}
	};
}
/*
mat4 DevaFramework::rotate(const Quaternion &q)
{

}
*/
mat4 Math::scale(vec3 scale_vector)
{
	return{ vec4{scale_vector[0], 0, 0, 0 }, vec4{0, scale_vector[1], 0, 0}, vec4{0, 0, scale_vector[2], 0}, vec4{0, 0, 0, 1} };
};

mat4 Math::translate(vec3 translation_vector)
{
	return{ 
		vec4{1, 0, 0, translation_vector[0]}, 
		vec4{0, 1, 0, translation_vector[1]}, 
		vec4{0, 0, 1, translation_vector[2]}, 
		vec4{0.f, 0.f, 0.f, 1.f} };
}

mat4 Math::projection(float fov, float aspectRatio, float zn, float zf) {

	float S = 1.0 / (std::tan(fov / 2));

	return {
		vec4{S, 0.f, 0.f, 0.f},
		vec4{0.f, S, 0.f , 0.f},
		vec4{0.f, 0.f, zf / (zn - zf), zf*zn / (zn - zf)},
		vec4{0.f, 0.f, -1.f, 0.f}
	};
}