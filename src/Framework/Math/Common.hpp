#ifndef DEVA_FRAMEWORK_MATH_COMMON_HPP
#define DEVA_FRAMEWORK_MATH_COMMON_HPP

#include "Config.hpp"
#include "Vector.hpp"
#include "Matrix.hpp"

namespace DevaFramework {

	template<typename T, size_t m1vecn, size_t m1vecl, size_t m2vecl>
	BaseMatrix<T, m1vecn, m2vecl> operator*(const BaseMatrix<T, m1vecn, m1vecl> &lhs, const BaseMatrix<T, m1vecl, m2vecl> &rhs) {
		BaseMatrix<T, m1vecn, m2vecl> result;
		for (int i = 0;i < m1vecn;i++)
		{
			for (int j = 0;j < m2vecl;j++)
			{
				//LOG << "result[" << i << "][" << j << "] = ";
				result(i, j) = 0;
				for (int k = 0;k < m1vecl;k++)
				{
					result(i, j) += lhs(i, k) * rhs(k, j);
					//LOG << "(" << lhs(i, k) << " * " << rhs(k, j) << " ) + ";
				}
				//LOG << "   = " << result(i, j) << LOG.endl;
			}
		}
		return result;
	}

	template<typename T, size_t m1vecn, size_t m1vecl>
	BaseVector<T, m1vecl> operator*(const BaseMatrix<T, m1vecn, m1vecl> &lhs, const BaseVector<T, m1vecl> &rhs) {
		BaseVector<T, m1vecl> result{0.0, 0.0, 0.0, 0.0};
		for (int k = 0;k < m1vecl;k++)
		{
			//LOG << "[0] -> ";
			for (int j = 0;j < m1vecn;j++)
			{
				result[k] += lhs(k, j) * rhs[j];
				//LOG << " + " << lhs(k, j) << " * " << rhs[j];
			}
			//LOG << " = " << result[k] << LOG.endl;
		}
		return result;
	}

	template<typename T, size_t n>
	BaseVector<T, n> operator+(const BaseVector<T, n> &lhs, const BaseVector<T, n> &rhs)
	{
		BaseVector<T, n> result;
		for (int i = 0;i < n;i++)
		{
			result[i] = lhs[i] + rhs[i];
		}
		return result;
	}
	template<typename T, size_t n>
	BaseVector<T, n> operator+(const BaseVector<T, n> &lhs, float rhs)
	{
		BaseVector<T, n> result;
		for (int i = 0;i < n;i++)
		{
			result[i] = lhs[i] + rhs;
		}
		return result;
	}

	template<typename T, size_t n>
	BaseVector<T, n> operator-(const BaseVector<T, n> &lhs, const BaseVector<T, n> &rhs)
	{
		BaseVector<T, n> result;
		for (int i = 0;i < n;i++)
		{
			result[i] = lhs[i] - rhs[i];
		}
		return result;
	}
	template<typename T, size_t n>
	BaseVector<T, n> operator-(const BaseVector<T, n> &lhs, float rhs)
	{
		BaseVector<T, n> result;
		for (int i = 0;i < n;i++)
		{
			result[i] = lhs[i] - rhs;
		}
		return result;
	}

	template<typename T, size_t n>
	BaseVector<T, n> operator*(const BaseVector<T, n> &lhs, const BaseVector<T, n> &rhs)
	{
		BaseVector<T, n> result;
		for (int i = 0;i < n;i++)
		{
			result[i] = lhs[i] * rhs[i];
		}
		return result;
	}
	template<typename T, size_t n>
	BaseVector<T, n> operator*(const BaseVector<T, n> &lhs, float rhs)
	{
		BaseVector<T, n> result;
		for (int i = 0;i < n;i++)
		{
			result[i] = lhs[i] * rhs;
		}
		return result;
	}

	template<typename T, size_t n>
	BaseVector<T, n> operator/(const BaseVector<T, n> &lhs, const BaseVector<T, n> &rhs)
	{
		BaseVector<T, n> result;
		for (int i = 0;i < n;i++)
		{
			result[i] = lhs[i] / rhs[i];
		}
		return result;
	}

	template<typename T, size_t n>
	BaseVector<T, n> operator/(const BaseVector<T, n> &lhs, float rhs)
	{
		BaseVector<T, n> result;
		for (int i = 0;i < n;i++)
		{
			result[i] = lhs[i] / rhs;
		}
		return result;
	}

	namespace Math {

		template<typename T, size_t n>
		float magnitude(const BaseVector<T, n> &v) {
			float sum = 0;
			for (int i = 0;i < n; i++)
			{
				sum += v[i] * v[i];
			}
			return sqrt(sum);
		}

		template<typename T, size_t n>
		BaseVector<T, n> normal(const BaseVector<T, n> &v) {
			BaseVector<T, n> result;
			float mag = magnitude(v);
			for (int i = 0;i < n;i++)
			{
				result[i] = v[i] / mag;
			}
			return result;
		}
	}

}

#endif //DEVA_FRAMEWORK_MATH_COMMON_HPP