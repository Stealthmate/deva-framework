#ifndef DEVA_FRAMEWORK_MATH_MATRIX_H
#define DEVA_FRAMEWORK_MATH_MATRIX_H

#include "BaseMatrix.hpp"

namespace DevaFramework
{
	typedef BaseMatrix<float, 2, 2> mat2;
	typedef BaseMatrix<float, 2, 3> mat2x3;
	typedef BaseMatrix<float, 2, 4> mat2x4;
	typedef BaseMatrix<float, 3, 2> mat3x2;
	typedef BaseMatrix<float, 3, 3> mat3;
	typedef BaseMatrix<float, 3, 4> mat3x4;
	typedef BaseMatrix<float, 4, 2> mat4x2;
	typedef BaseMatrix<float, 4, 3> mat4x3;
	typedef BaseMatrix<float, 4, 4> mat4;
}

#endif //DEVA_FRAMEWORK_MATH_MATRIX_H
