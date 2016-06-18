#ifndef DEVA_FRAMEWORK_GRAPHICS_SHADER_VARIABLE_TYPE_H
#define DEVA_FRAMEWORK_GRAPHICS_SHADER_VARIABLE_TYPE_H

#include "Config.hpp"

#include "glTypes.hpp"

namespace DevaFramework
{
	USE_GL;

	class ShaderVariableDataType
	{
	public:
		enum Type
		{
			T_FLOAT = 0,
			T_INT = 1,
			T_UINT = 2,
			T_BOOL = 3,

			T_FLOAT_VEC2 = 4,
			T_INT_VEC2 = 5,
			T_UINT_VEC2 = 6,
			T_BOOL_VEC2 = 7,

			T_FLOAT_VEC3 = 4,
			T_INT_VEC3 = 5,
			T_UINT_VEC3 = 6,
			T_BOOL_VEC3 = 7,

			T_FLOAT_VEC4 = 4,
			T_INT_VEC4 = 5,
			T_UINT_VEC4 = 6,
			T_BOOL_VEC4 = 7,
		};

	private:
		Type datatype;
		
	protected:
		DEVA_FRAMEWORK_API ShaderVariableDataType(Type datatype);

	public:

		DEVA_FRAMEWORK_API virtual void intializeAtID(GLuint ID) const =0;
		DEVA_FRAMEWORK_API virtual Type getType() const final;
	};
}


#endif //DEVA_FRAMEWORK_GRAPHICS_SHADER_VARIABLE_TYPE_H