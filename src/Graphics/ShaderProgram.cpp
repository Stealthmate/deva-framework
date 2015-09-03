#include "ShaderProgram.hpp"

#include "glFunctions.hpp"

#include "../src/System/Logger.hpp"

USE_GL;
using namespace DevaFramework;

const std::string ShaderProgram::LINK_STATUS_OK = "SHADERPROGRAM_LINK_SUCCESS";

ShaderProgram::ShaderProgram(const std::vector<Shader> &shaders)
	:shaders(10)
{
	this->handle = glCreateProgram();
	for (int i = 0;i < shaders.size();i++)
	{
		attachShader(shaders[i]);
	}
}

ShaderProgram::ShaderProgram(ShaderProgram &&sp)
{
	this->handle = sp.handle;
	sp.handle = SHADERPROGRAM_HANDLE_NULL;
	this->shaders = sp.shaders;
	sp.shaders.clear();
}

ShaderProgram& ShaderProgram::operator=(ShaderProgram &&sp) 
{
	if (this->handle != SHADERPROGRAM_HANDLE_NULL) glDeleteProgram(this->handle);
	this->handle = sp.handle;
	sp.handle = SHADERPROGRAM_HANDLE_NULL;
	this->shaders = sp.shaders;
	sp.shaders.clear();

	return *this;
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

ShaderProgram& ShaderProgram::detachShader(GLuint shaderHandle)
{
	auto i = std::find(this->shaders.begin(), this->shaders.end(), shaderHandle);
	if (i != this->shaders.end())
	{
		glAttachShader(this->handle, *i);
		this->shaders.erase(i);
	}

	return *this;
}

std::string ShaderProgram::link()
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
	
	for (auto i : shaders) glDetachShader(this->handle, i);
	shaders.clear();

	return LINK_STATUS_OK;
}

ShaderProgram::~ShaderProgram()
{
	if (this->handle != SHADERPROGRAM_HANDLE_NULL)
		for (auto i : shaders) glDetachShader(this->handle, i);

	glDeleteProgram(this->handle);
}