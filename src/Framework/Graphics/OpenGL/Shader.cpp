#ifdef DEVA_BUILD_OPENGL

#include "Shader.hpp"
#include "glFunctions.hpp"

#include <vector>

using namespace gl;
using namespace DevaFramework;

const std::string Shader::COMPILE_STATUS_OK = "SHADER_COMPILE_SUCCESS";

Shader::Shader(GLenum shaderType, const std::string &source)
{
	mHandle = glCreateShader(shaderType);
	setSource(source);
}

Shader::Shader(Shader &&shader)
{
	mHandle = shader.mHandle;
	shader.mHandle = SHADER_HANDLE_NULL;
	setSource(shader.source);
	shader.source = "";
}

Shader& Shader::operator=(Shader &&shader)
{
	if (mHandle == shader.mHandle) return *this;

	if(mHandle != SHADER_HANDLE_NULL) glDeleteShader(mHandle);
	mHandle = shader.mHandle;
	shader.mHandle = SHADER_HANDLE_NULL;
	setSource(shader.source);
	shader.source = "";
	return *this;
}

void Shader::setSource(const std::string &source)
{
	const GLchar * src[] = { &source[0] };
	glShaderSource(mHandle, 1, src, 0);
	this->source = source;
}

std::string Shader::compile() const
{
	glCompileShader(mHandle);
	GLint status;
	glGetShaderiv(mHandle, GL_COMPILE_STATUS, &status);
	if ((GLboolean)status != GL_TRUE)
	{
		GLint infoLogLength;
		glGetShaderiv(mHandle, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::vector<GLchar> log(infoLogLength);
		glGetShaderInfoLog(mHandle, infoLogLength, nullptr, &log[0]);
		std::string result(&log[0], &log[log.size()-1]);
		return result;
	}

	return COMPILE_STATUS_OK;
}

Shader::~Shader()
{
	if(mHandle != SHADER_HANDLE_NULL) glDeleteShader(mHandle);
}

#endif // DEVA_BUILD_OPENGL