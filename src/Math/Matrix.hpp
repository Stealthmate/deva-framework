#ifndef DEVA_FRAMEWORK_MATH_MATRIX_H
#define DEVA_FRAMEWORK_MATH_MATRIX_H

#include "BaseMatrix.hpp"
#include "Vector.hpp"

namespace DevaFramework
{
	typedef BaseMatrix<float, 2, 2> mat2x2;
	typedef BaseMatrix<float, 2, 3> mat2x3;
	typedef BaseMatrix<float, 2, 4> mat2x4;

	typedef BaseMatrix<float, 3, 2> mat3x2;
	typedef BaseMatrix<float, 3, 3> mat3x3;
	typedef BaseMatrix<float, 3, 4> mat3x4;

	typedef BaseMatrix<float, 4, 2> mat4x2;
	typedef BaseMatrix<float, 4, 3> mat4x3;
	typedef BaseMatrix<float, 4, 4> mat4x4;

	typedef mat2x2 mat2;
	typedef mat3x3 mat3;
	typedef mat4x4 mat4;

	inline mat3 mat4to3(const mat4 &matrix)
	{
		return mat3
		{
			vec3{ matrix(0, 0), matrix(0, 1), matrix(0, 2) },
			vec3{ matrix(1, 0), matrix(1, 1), matrix(1, 2) },
			vec3{ matrix(2, 0), matrix(2, 1), matrix(2, 2) }
		};
	}
	inline mat2 mat4to2(const mat4 &matrix)
	{
		return mat2
		{
			vec2{ matrix(0, 0), matrix(0, 1)},
			vec2{ matrix(1, 0), matrix(1, 1)}
		};
	}

	inline mat2 mat3to2(const mat3 &matrix)
	{
		return mat2
		{
			vec2{ matrix(0, 0), matrix(0, 1) },
			vec2{ matrix(1, 0), matrix(1, 1) }
		};
	}
}

#endif //DEVA_FRAMEWORK_MATH_MATRIX_H
