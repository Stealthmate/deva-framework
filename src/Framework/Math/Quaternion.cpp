#include "Quaternion.hpp"
#include "Common.hpp"

using namespace DevaFramework;

Quaternion::Quaternion()
{
	this->angle = 1;
	this->unit_axis = vec3{0, 0, 0};
}

Quaternion::Quaternion(float angle, const vec3 &axis)
{
	this->angle = angle;
	this->unit_axis = Math::normal(axis);
}