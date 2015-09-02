#ifndef DEVA_FRAMEOWORK_MATH_MATRIX_VECTOR_H
#define DEVA_FRAMEOWORK_MATH_MATRIX_VECTOR_H

#include "BaseMatrix.hpp"
#include <initializer_list>
#include <cmath>

namespace DevaFramework
{
	template<typename T, unsigned int vector_length>
	class BaseVector : public BaseMatrix<T, vector_length, 1> //ACTUALLY N_VECTORS!!!!!!!! 
	{

	public:

		BaseVector() : BaseMatrix() {}

		BaseVector(const std::initializer_list<T> &val)
		{
			auto val_i = val.begin();
			if (val.size() >= vector_length)
			{
				for (int i = 0;i <= vector_length;i++)
				{
					data[i] = *val_i;
					val_i++;
				}
			}
		}

		T& operator[](int i)
		{
			return operator()(0, i);
		}

		const T& operator[](int i) const
		{
			return operator()(0, 1);
		}

		typedef BaseVector<T, vector_length> Vector;

		BaseVector& operator+(const Vector &vec) const
		{
			Vector result;
			for (int i = 0;i <= vector_length - 1;i++)
			{
				result[i] = this->getValue(0, i) + vec.getValue(0, i);
			}
			return result;
		}

		BaseVector& operator-(const Vector &vec) const
		{
			Vector result;
			for (int i = 0;i <= vector_length - 1;i++)
			{
				result[i] = this->getValue(0, i) - vec.getValue(0, i);
			}
			return result;
		}

		BaseVector& operator*(const Vector &vec) const
		{
			Vector result;
			for (int i = 0;i <= vector_length - 1;i++)
			{
				result[i] = this->getValue(0, i) * vec.getValue(0, i);
			}
			return result;
		}

		BaseVector& operator/(const Vector &vec) const
		{
			Vector result;
			for (int i = 0;i <= vector_length - 1;i++)
			{
				result[i] = this->getValue(0, i) / vec.getValue(0, i);
			}
			return result;
		}

		double magnitude() const
		{
			double sum = 0;
			for (int i = 0;i <= vector_length - 1; i++)
			{
				sum += this->operator[](i) * this->operator[](i);
			}
			return sqrt(sum);
		}

		Vector normal() const
		{
			Vector result;
			double mag = this->magnitude();
			for (int i = 0;i <= vector_length - 1;i++)
			{
				result[i] = this->getValue(0, i) / mag;
			}
			return result;
		}
	};
}

#endif //DEVA_FRAMEOWORK_MATH_MATRIX_VECTOR_H