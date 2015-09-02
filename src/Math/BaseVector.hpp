#ifndef DEVA_FRAMEOWORK_MATH_MATRIX_VECTOR_H
#define DEVA_FRAMEOWORK_MATH_MATRIX_VECTOR_H

#include "BaseMatrix.hpp"
#include <initializer_list>
#include <cmath>

namespace DevaFramework
{
	/**
		@brief A generic class representing a \b column vector.

		@tparam T - the type of data in the vector
		@tparam vector_length - the number of values in the vector. For a column vector, this means the number
		of rows.
	*/
	template<typename T, unsigned int vector_length>
	class BaseVector : public BaseMatrix<T, vector_length, 1> //ACTUALLY N_VECTORS!!!!!!!! 
	{

		typedef BaseVector<T, vector_length> Vector;//Easier naming

	public:

		///Empty default constructor, calls BaseMatrix()
		BaseVector() : BaseMatrix() {}

		/**
			Takes an initializer list of \b T values and constructs a column vector

			@param values - the list of values to construct the vector from

			@throws std::invalid_argument - if the number of values in \b values is not equal to \b vector_length
		*/
		BaseVector(const std::initializer_list<T> &values)
		{
			if (values.size() != vector_length)
			{
				Logger::assert 
					<< Logger::err.stamp 
					<< "Tried to create vector with " 
					<< vector_length 
					<< " values, but passed " 
					<< values.size();

				throw std::invalid_argument(
					"Tried to create vector with " + strm(vector_length) + " values, but passed " + strm(values.size()));
			}
			auto val_i = values.begin();
			if (values.size() >= vector_length)
			{
				for (int i = 0;i <= vector_length;i++)
				{
					data[i] = *val_i;
					val_i++;
				}
			}
		}


		/**
			@param i - the number of the set

			@return A non-const reference to the i-th value in the vector. Can be modified or assigned to.
		*/
		T& operator[](int i)
		{
			return operator()(0, i);
		}

		/**
		@param i - the number of the set

		@return A const reference to the i-th value in the vector. CANNOT be modified or assigned to.
		*/
		const T& operator[](int i) const
		{
			return operator()(0, 1);
		}

		/**
			@param vec - a column vector with the same \b vector_length as \b this
			@return A column vector of size vector_length, where the i-th element is the sum of the i-th elements of
			\b this vector and \b vec
		*/
		BaseVector& operator+(const Vector &vec) const
		{
			Vector result;
			for (int i = 0;i <= vector_length - 1;i++)
			{
				result[i] = this->getValue(0, i) + vec.getValue(0, i);
			}
			return result;
		}

		/**
		@param vec - a column vector with the same \b vector_length as \b this
		@return A column vector of size vector_length, where the i-th element is the difference of the i-th elements of
		\b this vector and \b vec
		*/
		BaseVector& operator-(const Vector &vec) const
		{
			Vector result;
			for (int i = 0;i <= vector_length - 1;i++)
			{
				result[i] = this->getValue(0, i) - vec.getValue(0, i);
			}
			return result;
		}

		/**
		@param vec - a column vector with the same \b vector_length as \b this
		@return A column vector of size vector_length, where the i-th element is the product of the i-th elements of
		\b this vector and \b vec
		*/
		BaseVector& operator*(const Vector &vec) const
		{
			Vector result;
			for (int i = 0;i <= vector_length - 1;i++)
			{
				result[i] = this->getValue(0, i) * vec.getValue(0, i);
			}
			return result;
		}

		/**
		@param vec - a column vector with the same \b vector_length as \b this
		@return A column vector of size vector_length, where the i-th element is the quotient of the i-th elements of
		\b this vector and \b vec
		*/
		BaseVector& operator/(const Vector &vec) const
		{
			Vector result;
			for (int i = 0;i <= vector_length - 1;i++)
			{
				result[i] = this->getValue(0, i) / vec.getValue(0, i);
			}
			return result;
		}

		///@return The magnitude of the vector
		double magnitude() const
		{
			double sum = 0;
			for (int i = 0;i <= vector_length - 1; i++)
			{
				sum += this->operator[](i) * this->operator[](i);
			}
			return sqrt(sum);
		}

		///@return A unit vector with the same direction
		Vector normal() const
		{
			Vector result;
			double mag = this->magnitude();
			for (int i = 0;i <= vector_length - 1;i++)
			{
				result[i] = this->operator()(0, i) / mag;
			}
			return result;
		}
	};
}

#endif //DEVA_FRAMEOWORK_MATH_MATRIX_VECTOR_H