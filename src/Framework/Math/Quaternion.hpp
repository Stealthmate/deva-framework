#ifndef DEVA_FRAMEWORK_MATH_QUATERNION_H
#define DEVA_FRAMEWORK_MATH_QUATERNION_H

#include "Config.hpp"
#include "Vector.hpp"
#include "Matrix.hpp"

struct EulerAngles;

namespace DevaFramework
{
	class Quaternion
	{
	public:
		static Quaternion fromMatrix(const mat3 &matrix);


	private:

		float angle;
		vec3 unit_axis;

	public:

		DEVA_FRAMEWORK_API Quaternion();
		DEVA_FRAMEWORK_API Quaternion(float angle, const vec3 &axis);

	};
}

#endif //DEVA_FRAMEWORK_MATH_QUATERNION_H
