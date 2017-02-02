#ifndef DEVA_FRAMEWORK_GRAPHICS_SHADER_VARIABLE_TYPE_INT
#define DEVA_FRAMEWORK_GRAPHICS_SHADER_VARIABLE_TYPE_INT

#include "Config.hpp"
#include "ShaderVariableDataType.hpp"

namespace DevaFramework
{
	class ShaderVariableDataType_int : public ShaderVariableDataType
	{
		int data;

	public:

		DEVA_FRAMEWORK_API ShaderVariableDataType_int(int data);

		DEVA_FRAMEWORK_API virtual void initializeAtID(GLuint id) const;

	};
}

#endif //DEVA_FRAMEWORK_GRAPHICS_SHADER_VARIABLE_TYPE_INT
