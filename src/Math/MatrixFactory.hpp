#ifndef DEVA_FRAMEWORK_MATH_MATRIX_FACTORY_H
#define DEVA_FRAMEWORK_MATH_MATRIX_FACTORY_H

#include "Matrix.hpp"
#include "Vector.hpp"

#include "Config.hpp"

namespace DevaFramework
{


	DEVA_MATH_API mat4 rotate(float angle, vec3 axis);
	DEVA_MATH_API mat4 translate(vec3 translation_vec);
	DEVA_MATH_API mat4 scale(vec3 scale_vec);

}


#endif //DEVA_FRAMEWORK_MATH_MATRIX_FACTORY_H