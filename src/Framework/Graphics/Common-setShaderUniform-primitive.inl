//Float
void DevaFramework::setShaderUniform(
	gl::GLuint uniformid, float value, GLsizei count, GLboolean transpose)
{
	glUniform1f(uniformid, value);
}

void DevaFramework::setShaderUniform(gl::GLuint uniformid, const std::vector<float> &value, GLsizei count, GLboolean transpose)
{
	glUniform1fv(uniformid, count, &value[0]);
}

//Int
void DevaFramework::setShaderUniform(gl::GLuint uniformid, int value, GLsizei count, GLboolean transpose)
{
	glUniform1i(uniformid, value);
}

void DevaFramework::setShaderUniform(gl::GLuint uniformid, const std::vector<int> &value, GLsizei count, GLboolean transpose)
{
	glUniform1iv(uniformid, count, &value[0]);
}

//Unsigned int
void DevaFramework::setShaderUniform(gl::GLuint uniformid, unsigned int value, GLsizei count, GLboolean transpose)
{
	glUniform1ui(uniformid, value);
}

void DevaFramework::setShaderUniform(gl::GLuint uniformid, const std::vector<unsigned int> &value, GLsizei count, GLboolean transpose)
{
	glUniform1uiv(uniformid, count, &value[0]);
}