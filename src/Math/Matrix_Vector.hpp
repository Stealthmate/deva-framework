#ifndef DEVA_FRAMEOWORK_MATH_MATRIX_VECTOR_H
#define DEVA_FRAMEOWORK_MATH_MATRIX_VECTOR_H

#include "BaseMatrix.hpp"
#include <initializer_list>

namespace DevaFramework
{
	template<typename T, unsigned int vector_length>
	class base_vec : public BaseMatrix<T, vector_length, 1> //ACTUALLY N_VECTORS!!!!!!!! 
	{

	public:

		base_vec(const std::initializer_list<T> &val)
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

		T operator[](int i) const
		{
			if(i < vector_length) return operator(0, i);
			return 0;
		}
	};

	typedef base_vec<float, 2> vec2;
	typedef base_vec<float, 3> vec3;
	typedef base_vec<float, 4> vec4;
	
	typedef base_vec<double, 2> dvec2;
	typedef base_vec<double, 3> dvec3;
	typedef base_vec<double, 4> dvec4;
	
	typedef base_vec<unsigned int, 2> uvec2;
	typedef base_vec<unsigned int, 3> uvec3;
	typedef base_vec<unsigned int, 4> uvec4;

	typedef base_vec<int, 2> ivec2;
	typedef base_vec<int, 3> ivec3;
	typedef base_vec<int, 4> ivec4;
}

#endif //DEVA_FRAMEOWORK_MATH_MATRIX_VECTOR_H