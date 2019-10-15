#include "Shape.hpp"

using namespace DevaFramework;

Shape::Shape(const std::vector<vec3> &coords) : mCoords(coords) {}

std::vector<Triangle> Shape::triangulate() const {
	throw DevaUnsupportedOperationException("Shape::triangulate()");
}