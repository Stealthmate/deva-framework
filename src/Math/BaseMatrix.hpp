#ifndef DEVA_FRAMEWORK_MATH_BASE_MATRIX_H
#define DEVA_FRAMEWORK_MATH_BASE_MATRIX_H

#include <initializer_list>
#include <string>
#include <iostream>

#include "Config.hpp"
#include "../src/System/Logger.hpp"
#include "../src/System/Exceptions.hpp"

namespace DevaFramework
{
	/**
		
		@brief A generic class, representing an NxM matrix

		Every matrix is to be seen as \b n_vectors sets of \b vector_length values, 
		where values in a set and individual sets
		are stored consecutively. This allows a matrix to be seen as either row-major or column-major

		@tparam T - the type of the matrix. On theory, a matrix can be of any type that supports all of the following:<br />
		 <ul>
		 <li>Default construction                 </li><br />
		 <li>Binary * (star) operator             </li><br />
		 <li>Copy and Move assignment             </li><br />
		 <li>String conversion via std::to_string </li><br />

		@tparam n_vectors - The number of sets in the matrix. Every set represents a column.

		@tparam vector_length - The number of values in a set.
	*/
	template<typename T, unsigned int n_vectors, unsigned int vector_length>
	class BaseMatrix
	{
	protected:
		T data[n_vectors*vector_length];

	public:


		///Default constructs every element in the matrix
		BaseMatrix()
		{
			for (int i = 0;i <= n_vectors - 1;i++)
			{
				for (int j = 0;j <= vector_length - 1;j++)
				{
					data[i*vector_length + j] = T();
				}
			}
		}


		/**
			Takes an initializer list of vectors with a length of \b vector_length
			and constructs a matrix where each of these vectors represents a set in the matrix.

			@param values - the list of vectors to construct the matrix from

			@throws std::invalid_argument - if the number of values in \b values is not equal to \b n_vectors
		*/
		BaseMatrix(const std::initializer_list<BaseMatrix<T, vector_length, 1>> &values)
		{
			if (values.size() != n_vectors)
			{
				throw DevaInvalidInputException(
					"Tried to create matrix with " + strm(n_vectors) + " columns, but passed " + strm(values.size()));
			}
			auto val_i = values.begin();
			for (int i = 0;i <= n_vectors;i++)
			{
				for (int j = 0;j <= vector_length - 1;j++)
				{
					data[i * vector_length + j] = (*val_i)(0, j);
				}
				val_i++;
			}
		}

		/**
			Takes an initializer list of \b T values to initialize the matrix with.

			@param values - the list of values

			@throws std::invalid_argument - if the number of values in \b values is not equal to
			\b n_vectors * \b vector_length
		
		*/
		BaseMatrix(const std::initializer_list<float> values)
		{
			static_assert(values.size() == n_vectors*vector_length, "Not correct number of values.");
			auto val_i = list.begin();

		}


		BaseMatrix(const BaseMatrix &mat) = default;
		BaseMatrix(BaseMatrix &&mat) = default;
		BaseMatrix& operator=(const BaseMatrix &mat) = default;
		BaseMatrix& operator=(BaseMatrix &&mat) = default;



		/**
			@param vec_n - the number of the set
			@param vec_pos - the position in the set

			@return A non-const reference to the value in the matrix at position
			\b vec_pos in set \b vec_n. Can be modified or assigned to.
		*/
		T& operator()(unsigned int vec_n, unsigned int vec_pos)
		{
			return data[vec_n * vector_length + vec_pos];
		}

		/**
			@param vec_n - the number of the set
			@param vec_pos - the position in the set		

			@return A const reference to the value in the matrix at position
			\b vec_pos in set \b vec_n. CANNOT be modified or assigned to.
		*/
		const T& operator()(unsigned int vec_n, unsigned int vec_pos) const
		{
			return data[vec_n * vector_length + vec_pos];
		}


		/**
			@return A const T* const pointer to the first element of the memory block of the matrix. 
			The data inside is read-only and
			cannot be modified. Can be to set uniform matrices in OpenGL functions.
		*/
		operator const T* const() const
		{
			return &data[0];
		}


		/**
			Returns the product of two matrices. The set length of the left matrix (\b this)
			must be equal to the number of sets of the right matrix (\b mat)

			@param mat - the right matrix in the multiplication operation

			@return A matrix with \b n_vectors columns of length \b vec_len, which is the product of \b this and \b mat
		*/
		template<unsigned int vec_len>
		BaseMatrix<T, n_vectors, vec_len> operator*(const BaseMatrix<T, vector_length, vec_len> &mat) const
		{
			BaseMatrix<T, n_vectors, vec_len> result;
			for (int k = 0;k <= vector_length - 1;k++)
			{
				for (int i = 0;i <= vec_len - 1;i++)
				{
					for (int j = 0;j <= n_vectors - 1;j++)
					{
						result(i, k) += (*this)(k, j) * mat(i, j);
					}
				}
			}
			return result;
		}


		///@return A string representation of the matrix
		virtual std::string to_str() const
		{
			std::string res = "\nMat" + strm(n_vectors) + "x" + strm(vector_length) + ":\n";
			for (int i = 0;i <= n_vectors - 1;i++)
			{
				for (int j = 0;j <= vector_length - 1;j++)
				{
					res += strm(data[i*vector_length + j]) + " ";
				}
				res += "\n";
			}
			return res;
		}

	};
}


#endif //DEVA_FRAMEWORK_MATH_BASE_MATRIX_H