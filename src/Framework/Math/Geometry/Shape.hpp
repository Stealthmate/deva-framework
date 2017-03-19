#ifndef DEVA_FRAMEWORK_MATH_SHAPE_HPP
#define DEVA_FRAMEWORK_MATH_SHAPE_HPP

#include "../Config.hpp"

#include "../Vector.hpp"
#include <vector>

namespace DevaFramework {
	
	class Triangle;

	//Immutable

	class Shape {
	public:

		DEVA_FRAMEWORK_API Shape(const std::vector<vec3> &coords);

		DEVA_FRAMEWORK_API virtual const std::vector<vec3>& coords() const noexcept { return mCoords; }

		DEVA_FRAMEWORK_API virtual std::vector<Triangle> triangulate() const;

	private:
		std::vector<vec3> mCoords;
	};
}

#endif // DEVA_FRAMEWORK_MATH_SHAPE_HPP