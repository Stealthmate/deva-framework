#ifndef DEVA_FRAMEWORK_MATH_EULER_ANGLES_H
#define DEVA_FRAMEWORK_MATH_EULER_ANGLES_H

#include "Config.hpp"

#include "Matrix.hpp"
#include "Quaternion.hpp"

namespace DevaFramework
{
	struct EulerAngles
	{
		float yaw;
		float pitch;
		float roll;

		DEVA_FRAMEWORK_API EulerAngles();
		DEVA_FRAMEWORK_API EulerAngles(float yaw, float pitch, float roll);
		DEVA_FRAMEWORK_API EulerAngles(const mat4 &matrix);
		DEVA_FRAMEWORK_API EulerAngles(const Quaternion &q);
	};
}

#endif //DEVA_FRAMEWORK_MATH_EULER_ANGLES_H