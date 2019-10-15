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
	template<typename T, size_t vector_length>
	class BaseVector : public BaseMatrix<T, vector_length, 1> //ACTUALLY N_VECTORS!!!!!!!! 
	{
		typedef BaseMatrix<T, vector_length, 1> super;
		typedef BaseVector<T, vector_length> Vector;

	public:

		BaseVector() : BaseMatrix<T, vector_length, 1>() {}

		/**
			Takes an initializer list of \b T values and constructs a column vector

			@param values - the list of values to construct the vector from

			@throws std::invalid_argument - if the number of values in \b values is not equal to \b vector_length
		*/
		constexpr BaseVector(const std::initializer_list<T> &values)
		{
			assert(values.size() == vector_length);
			
			auto val_i = values.begin();
			for (int i = 0;i < vector_length;i++)
			{
				this->data[i] = *val_i;
				val_i++;
			}
		}

		/**
			@param i - the number of the set

			@return A non-const reference to the i-th value in the vector. Can be modified or assigned to.
		*/
		T& operator[](size_t i)
		{
			assert(i < vector_length);
			return super::operator()(0, i);
		}

		/**
		@param i - the number of the set

		@return A const reference to the i-th value in the vector. CANNOT be modified or assigned to.
		*/
		const T& operator[](size_t i) const
		{
			assert(i < vector_length);
			return super::operator()(0, i);
		}
	};

	template<typename T, size_t n>
	std::string strf(const BaseVector<T, n> &v) {
		std::string str = "vec" + strf(n) + " [ ";
		for (int i = 0;i < n;i++)
		{
			str += strf(v[i]);
			if (i<n - 1) str += " ; ";
		}
		str += "]";
		return str;
	}
}

#endif //DEVA_FRAMEOWORK_MATH_MATRIX_VECTOR_H
