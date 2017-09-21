#ifndef DEVA_FRAMEWORK_MATH_BASE_MATRIX_H
#define DEVA_FRAMEWORK_MATH_BASE_MATRIX_H

#include "Config.hpp"

#include "../Core/Serialization/Binary/BinarySerializable.hpp"
#include "../Util/ByteBuffer.hpp"

#include <initializer_list>
#include <string>
#include <array>

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
		static_assert(std::is_arithmetic_v<T>, "Cannot create matrix with non-arithmetic type");
	protected:
		T data[n_vectors*vector_length];

	public:


		///Creates an identity matrix
		constexpr BaseMatrix()
		{
			for (int i = 0;i < n_vectors;i++)
			{
				for (int j = 0;j < vector_length;j++)
				{
					data[i*vector_length + j] = 0;
					if (i == j) data[i*vector_length + j] = 1;
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
			assert(values.size() == n_vectors);

			auto val_i = values.begin();
			for (int i = 0;i < n_vectors;i++)
			{
				for (int j = 0;j < vector_length;j++)
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
			auto val_i = values.begin();

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
		operator const T* () const
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
			for (int k = 0;k < vector_length;k++)
			{
				for (int i = 0;i < vec_len;i++)
				{
					for (int j = 0;j < n_vectors;j++)
					{
						result(i, k) += (*this)(k, j) * mat(i, j);
					}
				}
			}
			return result;
		}

		std::array<byte_t, n_vectors * vector_length * sizeof(T)> asBytes() const
		{
			std::array<byte_t, n_vectors * vector_length * sizeof(T)> arr;
			memcpy(arr.data(), data, arr.max_size());
			return arr;
		}

		///@return A string representation of the matrix
		std::string to_str() const
		{
			std::string res = "\nMat" + strm(n_vectors) + "x" + strm(vector_length) + ":\n";
			for (int i = 0;i < n_vectors;i++)
			{
				for (int j = 0;j < vector_length;j++)
				{
					res += strm(data[i*vector_length + j]) + " ";
				}
				res += "\n";
			}
			return res;
		}

	};


	template<typename T, unsigned int n, unsigned int m>
	struct SerialFixedSize<BaseMatrix<T, n, m>> {
		static constexpr size_t v = n * m * sizeof(T);
	};

	template<typename T, unsigned int n, unsigned int m>
	struct BinarySerializer<BaseMatrix<T, n, m>> {
	public:
		void operator()(const BaseMatrix<T, n, m> &mat, ByteOutputStream &stream) const {
			for (int i = 0;i < n;i++) {
				for (int j = 0;j < m;j++) {
					stream << mat(i, j);
				}
			}
		}
	};

	template<typename T, unsigned int n, unsigned int m>
	struct BinaryDeserializer<BaseMatrix<T, n, m>> {
	public:
		BaseMatrix<T, n, m> operator()(ByteInputStream &stream) const {
			BaseMatrix<T, n, m> mat;
			for (int i = 0;i < n;i++) {
				for (int j = 0;j < m;j++) {
					stream >> mat(i, j);
				}
			}
			return mat;
		}
	};

}


#endif //DEVA_FRAMEWORK_MATH_BASE_MATRIX_H
