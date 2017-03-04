#ifdef DEVA_BUILD_OPENGL

#include "ShaderProgram.hpp"

#include "glFunctions.hpp"
#include <algorithm>

USE_GL;
using namespace DevaFramework;

const std::string ShaderProgram::LINK_STATUS_OK = "SHADERPROGRAM_LINK_SUCCESS";

ShaderProgram::ShaderProgram(const std::vector<Shader> &shaders)
	:shaders(10)
{
	mHandle = glCreateProgram();
	for (int i = 0;i < shaders.size();i++)
	{
		attachShader(shaders[i]);
	}
}

ShaderProgram::ShaderProgram(ShaderProgram &&sp)
{
	mHandle = sp.mHandle;
	sp.mHandle = SHADERPROGRAM_HANDLE_NULL;
	this->shaders = sp.shaders;
	sp.shaders.clear();
}

ShaderProgram& ShaderProgram::operator=(ShaderProgram &&sp) 
{
	if (mHandle != SHADERPROGRAM_HANDLE_NULL) glDeleteProgram(mHandle);
	mHandle = sp.mHandle;
	sp.mHandle = SHADERPROGRAM_HANDLE_NULL;
	this->shaders = sp.shaders;
	sp.shaders.clear();

	return *this;
}

ShaderProgram& ShaderProgram::attachShader(const Shader &shader)
{
	if (std::find(this->shaders.begin(), this->shaders.end(), shader.handle()) == this->shaders.end())
	{
		glAttachShader(mHandle, shader.handle());
		this->shaders.push_back(shader.handle());
	}

	return *this;
}

ShaderProgram& ShaderProgram::detachShader(GLuint shaderHandle)
{
	auto i = std::find(this->shaders.begin(), this->shaders.end(), shaderHandle);
	if (i != this->shaders.end())
	{
		glAttachShader(mHandle, *i);
		this->shaders.erase(i);
	}

	return *this;
}

std::string ShaderProgram::link()
{
	glLinkProgram(mHandle);
	GLint status;
	glGetProgramiv(mHandle, GL_LINK_STATUS, &status);
	if ((GLboolean)status != GL_TRUE)
	{
		GLint infoLogLength;
		glGetProgramiv(mHandle, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar * log = new GLchar[infoLogLength];
		glGetProgramInfoLog(mHandle, infoLogLength, nullptr, log);
		std::string result(log);
		delete[] log;
		return result;
	}
	
	for (auto i : shaders) glDetachShader(mHandle, i);
	shaders.clear();

	return LINK_STATUS_OK;
}

ShaderProgram::~ShaderProgram()
{
	if (mHandle != SHADERPROGRAM_HANDLE_NULL)
		for (auto i : shaders) glDetachShader(mHandle, i);

	glDeleteProgram(mHandle);
}

#endif // DEVA_BUILD_OPENGL