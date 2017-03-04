#ifdef DEVA_BUILD_OPENGL

#include "ShaderVariableDataType.hpp"

namespace
{
	using namespace DevaFramework;
}

ShaderVariableDataType::ShaderVariableDataType(ShaderVariableDataType::Type datatype) : datatype(datatype) {}

ShaderVariableDataType::Type ShaderVariableDataType::getType() const { return this->datatype; }

#endif // DEVA_BUILD_OPENGL