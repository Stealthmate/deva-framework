#include "Common.hpp"

#include <vector>
#include <fstream>
#include <iostream>

using namespace gl;
using namespace glbinding;

GLuint DevaFramework::loadShaderSet(std::string VertexShaderCode, std::string FragmentShaderCode)
{
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	GLint Result = 0;
	int InfoLogLength;
	std::string err_msg;

	char const * ptrSource = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &ptrSource, NULL);
	glCompileShader(VertexShaderID);

	ptrSource = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &ptrSource, NULL);
	glCompileShader(FragmentShaderID);

	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);

	glLinkProgram(ProgramID);

	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		std::vector<char> ProgramErrMsg(10000);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrMsg[0]);
		if (ProgramErrMsg[0] != 0)
		{
			std::string err_msg = std::string(ProgramErrMsg.begin(), ProgramErrMsg.end());
			err_msg = err_msg.substr(0, err_msg.find_last_not_of('\0')+1);
			std::cout << err_msg << std::endl;
		}
	}

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}