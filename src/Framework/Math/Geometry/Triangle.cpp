#include "Triangle.hpp"

using namespace DevaFramework;

Triangle::Triangle(const vec3 &p1, const vec3 &p2, const vec3 &p3) : Shape(std::vector<vec3>{p1, p2, p3})
{
	mAngles = {};
}

std::vector<Triangle> Triangle::triangulate() const {
	return std::vector<Triangle>{*this};
}