#include "Shader.hpp"
#include "glFunctions.hpp"

USE_GL;
#include "../src/System/Logger.hpp"
using namespace DevaFramework;

const std::string Shader::COMPILE_STATUS_OK = "SHADER_COMPILE_SUCCESS";

Shader::Shader(GLenum shaderType, const std::string &source)
{

	this->handle = glCreateShader(shaderType);
	setSource(source);
}

Shader::Shader(Shader &&shader)
{
	this->handle = shader.handle;
	shader.handle = SHADER_HANDLE_NULL;
	setSource(shader.source);
	shader.source = "";
}

Shader& Shader::operator=(Shader &&shader)
{
	if (this->handle == shader.handle) return *this;

	if(this->handle != SHADER_HANDLE_NULL) glDeleteShader(this->handle);
	this->handle = shader.handle;
	shader.handle = SHADER_HANDLE_NULL;
	setSource(shader.source);
	shader.source = "";
	return *this;
}

void Shader::setSource(const std::string &source)
{
	const GLchar * src[] = { &source[0] };
	glShaderSource(this->handle, 1, src, 0);
	this->source = source;
}

std::string Shader::compile() const
{
	glCompileShader(this->handle);
	GLint status;
	glGetShaderiv(this->handle, GL_COMPILE_STATUS, &status);
	if ((GLboolean)status != GL_TRUE)
	{
		GLint infoLogLength;
		glGetShaderiv(this->handle, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar * log = new GLchar[infoLogLength];
		glGetShaderInfoLog(this->handle, infoLogLength, nullptr, log);
		std::string result(log);
		delete[] log;
		return result;
	}

	return COMPILE_STATUS_OK;
}

Shader::~Shader()
{
	if(this->handle != SHADER_HANDLE_NULL) glDeleteShader(this->handle);
}