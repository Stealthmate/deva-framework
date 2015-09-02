#ifndef DEVA_FRAMEWORK_MATH_MATRIX_FACTORY_H
#define DEVA_FRAMEWORK_MATH_MATRIX_FACTORY_H

#include "Matrix.hpp"
#include "Vector.hpp"

#include "Config.hpp"

namespace DevaFramework
{

	/**
		@param angle - angle of rotation
		@param axis - axis of rotation
		@return A 4x4 float matrix, representing a rotation of \b angle radians around \b axis 
	*/
	DEVA_MATH_API mat4 rotate(float angle, vec3 axis);
	/**
		@return A 4x4 float matrix, representing a translation operation with vector \b translation_vec
	*/
	DEVA_MATH_API mat4 translate(vec3 translation_vec);
	/**
		@return A 4x4 float matrix, representing a scale operation with vector \b scale_vec
	*/
	DEVA_MATH_API mat4 scale(vec3 scale_vec);

}


#endif //DEVA_FRAMEWORK_MATH_MATRIX_FACTORY_H