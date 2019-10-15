#ifndef DEVA_FRAMEWORK_GRAPHICS_OPENGL_COMMON_H
#define DEVA_FRAMEWORK_GRAPHICS_OPENGL_COMMON_H

#include "Config.hpp"

#include "glTypes.hpp"

#include "VertexBufferObject.hpp"
#include "../../Math/Vector.hpp"
#include "../../Math/Matrix.hpp"

namespace DevaFramework
{
	DEVA_FRAMEWORK_API gl::GLuint loadShaderSet(std::string VertexShaderCode, std::string FragmentShaderCode);


	DEVA_FRAMEWORK_API void setShaderUniform(gl::GLuint uniformid, float value, gl::GLsizei count = 1, gl::GLboolean transpose = gl::GL_FALSE);
	DEVA_FRAMEWORK_API void setShaderUniform(gl::GLuint uniformid, const std::vector<float> &value, gl::GLsizei count = 1, gl::GLboolean transpose = gl::GL_FALSE);
	DEVA_FRAMEWORK_API void setShaderUniform(gl::GLuint uniformid, int value, gl::GLsizei count = 1, gl::GLboolean transpose = gl::GL_FALSE);
	DEVA_FRAMEWORK_API void setShaderUniform(gl::GLuint uniformid, const std::vector<int> &value, gl::GLsizei count = 1, gl::GLboolean transpose = gl::GL_FALSE);
	DEVA_FRAMEWORK_API void setShaderUniform(gl::GLuint uniformid, unsigned int value, gl::GLsizei count = 1, gl::GLboolean transpose = gl::GL_FALSE);
	DEVA_FRAMEWORK_API void setShaderUniform(gl::GLuint uniformid, const std::vector<unsigned int> &value, gl::GLsizei count = 1, gl::GLboolean transpose = gl::GL_FALSE);

#define REGISTER_FUNCS(TYPE) \
DEVA_FRAMEWORK_API void setShaderUniform(gl::GLuint uniformid, const TYPE &value, gl::GLsizei count = 1, gl::GLboolean transpose = gl::GL_FALSE); \
DEVA_FRAMEWORK_API void setShaderUniform(gl::GLuint uniformid, const std::vector<TYPE> &value, gl::GLsizei count = 1, gl::GLboolean transpose = gl::GL_FALSE);

	REGISTER_FUNCS(vec2);
	REGISTER_FUNCS(ivec2);
	REGISTER_FUNCS(uvec2);

	REGISTER_FUNCS(vec3);
	REGISTER_FUNCS(ivec3);
	REGISTER_FUNCS(uvec3);

	REGISTER_FUNCS(vec4);
	REGISTER_FUNCS(ivec4);
	REGISTER_FUNCS(uvec4);

#undef REGISTER_FUNCS
#define REGISTER_FUNCS(TYPE) \
DEVA_FRAMEWORK_API void setShaderUniform(gl::GLuint uniformid, const std::vector<TYPE> &value, gl::GLsizei count = 1, gl::GLboolean transpose = gl::GL_FALSE); \
inline void setShaderUniform(gl::GLuint uniformid, const TYPE &value, gl::GLsizei count = 1, gl::GLboolean transpose = gl::GL_FALSE) { return setShaderUniform(uniformid, std::vector<TYPE>{value}, count, transpose); }

	REGISTER_FUNCS(mat2);
	REGISTER_FUNCS(mat2x3);
	REGISTER_FUNCS(mat2x4);

	REGISTER_FUNCS(mat3x2);
	REGISTER_FUNCS(mat3);
	REGISTER_FUNCS(mat3x4);

	REGISTER_FUNCS(mat4x2);
	REGISTER_FUNCS(mat4x3);
	REGISTER_FUNCS(mat4x4);

#undef REGISTER_FUNCS
}

#endif // DEVA_FRAMEWORK_GRAPHICS_OPENGL_COMMON_H