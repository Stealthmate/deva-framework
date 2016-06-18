#ifndef DEVA_FRAMEWORK_MATH_MATRIX_FACTORY_H
#define DEVA_FRAMEWORK_MATH_MATRIX_FACTORY_H

#include "Config.hpp"

#include "Matrix.hpp"
#include "Vector.hpp"
//#include "Quaternion.hpp"

namespace DevaFramework
{

	/**
		@param angle - angle of rotation
		@param axis - axis of rotation
		@return A 4x4 float matrix, representing the rotation
	*/
	DEVA_FRAMEWORK_API mat4 rotate(float angle, const vec3 axis);

	///Shorthand for rotate(angle, vec3{1, 0, 0});
	inline mat4 rotateX(float angle) { return rotate(angle, vec3{ 1, 0, 0 }); }
	///Shorthand for rotate(angle, vec{0, 1, 0,});
	inline mat4 rotateY(float angle) { return rotate(angle, vec3{ 0, 1, 0 }); }
	///Shorthand for rotate(angle, vec{0, 0, 1,});
	inline mat4 rotateZ(float angle) { return rotate(angle, vec3{ 0, 0, 1 }); }

	///Alias for rotateX
	constexpr auto pitch = rotateX;
	///Alias for rotateY
	constexpr auto yaw = rotateY;
	///Alias for rotateZ
	constexpr auto roll = rotateZ;

	/**
		@param q - a Quaternion representing the rotation
		@return A 4x4 float matrix, representing the rotation
	*/
	//DEVA_FRAMEWORK_API mat4 rotate(const Quaternion &q);

	/**
		@return A 4x4 float matrix, representing a translation operation with vector \b translation_vec
	*/
	DEVA_FRAMEWORK_API mat4 translate(vec3 translation_vec);
	/**
		@return A 4x4 float matrix, representing a scale operation with vector \b scale_vec
	*/
	DEVA_FRAMEWORK_API mat4 scale(vec3 scale_vec);

	//DEVA_FRAMEWORK_API mat4 project(vec3 camera_pos, float fl);

}


#endif //DEVA_FRAMEWORK_MATH_MATRIX_FACTORY_H