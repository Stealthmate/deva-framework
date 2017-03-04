#ifdef DEVA_BUILD_OPENGL

#include "ShaderVariableDataType_int.hpp"

#include "glFunctions.hpp"

namespace
{
	using namespace DevaFramework;
	using vartype = ShaderVariableDataType;
	using vartype_int = ShaderVariableDataType_int;
}

vartype_int::ShaderVariableDataType_int(int data) : vartype(vartype::Type::T_INT), data(data) {}


void vartype_int::initializeAtID(GLuint id) const
{
	glUniform1i(id, data);
}

#endif // DEVA_BUILD_OPENGL