#include "ShaderProgram.hpp"

#include "glFunctions.hpp"

#include "../src/System/Logger.hpp"

USE_GL;
using namespace DevaFramework;

const std::string ShaderProgram::LINK_STATUS_OK = "SHADERPROGRAM_LINK_SUCCESS";

ShaderProgram::ShaderProgram(const std::vector<Shader> &shaders)
{
	this->handle = glCreateProgram();
	for (auto i : shaders)
	{
		attachShader(i);
	}
}

ShaderProgram& ShaderProgram::attachShader(const Shader &shader)
{
	if (std::find(this->shaders.begin(), this->shaders.end(), shader.getHandle()) == this->shaders.end())
	{
		glAttachShader(this->handle, shader.getHandle());
		this->shaders.push_back(shader.getHandle());
	}

	return *this;
}

ShaderProgram& ShaderProgram::detachShader(const Shader &shader)
{
	auto i = std::find(this->shaders.begin(), this->shaders.end(), shader.getHandle());
	if (i != this->shaders.end())
	{
		glAttachShader(this->handle, *i);
		this->shaders.erase(i);
	}

	return *this;
}

std::string ShaderProgram::link() const
{
	glLinkProgram(this->handle);
	GLint status;
	glGetProgramiv(this->handle, GL_LINK_STATUS, &status);
	if ((GLboolean)status != GL_TRUE)
	{
		GLint infoLogLength;
		glGetProgramiv(this->handle, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar * log = new GLchar[infoLogLength];
		glGetProgramInfoLog(this->handle, infoLogLength, nullptr, log);
		std::string result(log);
		delete[] log;
		return result;
	}

	return LINK_STATUS_OK;
}

ShaderProgram::~ShaderProgram()
{
	if (this->handle != SHADERPROGRAM_HANDLE_NULL)
		for (auto i : shaders) glDetachShader(this->handle, i);

	glDeleteProgram(this->handle);
}