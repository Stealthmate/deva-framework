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

	typedef BaseMatrix<double, 2, 2> dmat2x2;
	typedef BaseMatrix<double, 2, 3> dmat2x3;
	typedef BaseMatrix<double, 2, 4> dmat2x4;

	typedef BaseMatrix<double, 3, 2> dmat3x2;
	typedef BaseMatrix<double, 3, 3> dmat3x3;
	typedef BaseMatrix<double, 3, 4> dmat3x4;

	typedef BaseMatrix<double, 4, 2> dmat4x2;
	typedef BaseMatrix<double, 4, 3> dmat4x3;
	typedef BaseMatrix<double, 4, 4> dmat4x4;

	typedef mat2x2 mat2;
	typedef mat3x3 mat3;
	typedef mat4x4 mat4;

	template<typename T>
	inline BaseMatrix<T, 3, 3> mat4to3(const BaseMatrix<T, 4, 4> &matrix)
	{
		return BaseMatrix<T, 3, 3>
		{
			BaseVector<T, 3>{ matrix(0, 0), matrix(0, 1), matrix(0, 2) },
			BaseVector<T, 3>{ matrix(1, 0), matrix(1, 1), matrix(1, 2) },
			BaseVector<T, 3>{ matrix(2, 0), matrix(2, 1), matrix(2, 2) }
		};
	}

	template<typename T>
	inline BaseMatrix<T, 2, 2> mat4to2(const BaseMatrix<T, 4, 4> &matrix)
	{
		return BaseMatrix<T, 2, 2>
		{
			BaseVector<T, 2>{ matrix(0, 0), matrix(0, 1)},
			BaseVector<T, 2>{ matrix(1, 0), matrix(1, 1)}
		};
	}

	template<typename T>
	inline BaseMatrix<T, 2, 2> mat3to2(const BaseMatrix<T, 3, 3> &matrix)
	{
		return BaseMatrix<T, 2, 2>
		{
			BaseVector<T, 2>{ matrix(0, 0), matrix(0, 1) },
			BaseVector<T, 2>{ matrix(1, 0), matrix(1, 1) }
		};
	}
}

#endif //DEVA_FRAMEWORK_MATH_MATRIX_H
