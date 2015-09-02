#ifndef DEVA_FRAMEWORK_MATH_BASE_MATRIX_H
#define DEVA_FRAMEWORK_MATH_BASE_MATRIX_H

#include <initializer_list>
#include <string>
#include <iostream>
namespace DevaFramework
{
	template<typename T, unsigned int n_vectors, unsigned int vector_length>
	class BaseMatrix
	{
		protected:
			T data[n_vectors*vector_length];
			friend class BaseMatrix;

		public:

			BaseMatrix()
			{
				for (int i = 0;i <= n_vectors - 1;i++)
				{
					for (int j = 0;j <= vector_length - 1;j++)
					{
						data[i*vector_length + j] = 0;
					}
				}
			}

			BaseMatrix(const std::initializer_list<BaseMatrix<T, vector_length, 1>> &list)
			{
				auto val_i = list.begin();
				if (list.size() >= n_vectors)
				{
					for (int i = 0;i <= n_vectors;i++)
					{
						for (int j = 0;j <= vector_length - 1;j++)
						{
							data[i * vector_length + j] = val_i->getValue(0, j);
						}
						val_i++;
					}
				}
			}

			BaseMatrix(const BaseMatrix &mat)
			{
				for (int i = 0;i <= (n_vectors*vector_length) - 1; i++)
				{
					this->data[i] = mat.data[i];
				}
			}


			T& operator()(unsigned int vec_n, unsigned int vec_pos)
			{
				return data[vec_n * vector_length + vec_pos];
			}

			T getValue(unsigned int vec_n, unsigned int vec_pos) const
			{
				return data[vec_n * vector_length + vec_pos];
			}

			explicit operator T*()
			{
				return &data[0];
			}

			template<unsigned int vec_len>
			BaseMatrix<T, n_vectors, vec_len> operator*(const BaseMatrix<T, vector_length, vec_len> &mat) const
			{
				BaseMatrix<T, n_vectors, vec_len> result;
				Logger::log(to_str());
				Logger::log(mat.to_str());
				for (int k = 0;k <= vector_length - 1;k++)
				{
					for (int i = 0;i <= vec_len - 1;i++)
					{
						for (int j = 0;j <= n_vectors - 1;j++)
						{
							result(i, k) += this->getValue(k, j) * mat.getValue(i, j);
						}
					}
				}
				return result;
			}

			std::string to_str() const
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