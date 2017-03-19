#ifndef DEVA_FRAMEWORK_MATH_GEOMETRY_TRIANGLE_HPP
#define DEVA_FRAMEWORK_MATH_GEOMETRY_TRIANGLE_HPP

#include "Config.hpp"
#include "Shape.hpp"
#include <tuple>

namespace DevaFramework {

	class Triangle : public Shape {
	public:

		DEVA_FRAMEWORK_API Triangle(const vec3 &p1, const vec3 &p2, const vec3 &p3);

		DEVA_FRAMEWORK_API const std::tuple<float, float, float>& angles() const noexcept { return mAngles; }
		DEVA_FRAMEWORK_API const std::tuple<float, float, float>& edges() const noexcept { return mEdges; }

		DEVA_FRAMEWORK_API virtual std::vector<Triangle> triangulate() const override;

	private:
		std::tuple<float, float, float> mAngles;
		std::tuple<float, float, float> mEdges;
	};

}

#endif // DEVA_FRAMEWORK_MATH_GEOMETRY_TRIANGLE_HPP