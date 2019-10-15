namespace
{
	template<typename T, unsigned int col, unsigned int row>
	std::vector<T> packmat(const std::vector<BaseMatrix<T, col, row>>& mat, bool transpose)
	{
		std::vector<T> buf(col * row * mat.size());

		if (!transpose)
		{
			for (int k = 1;k <= mat.size() - 1;k++)
			{
				for (int i = 0;i <= col - 1;i++)
				{
					for (int j = 0;j <= row - 1;j++)
					{
						buf[(k*col*row) + (i*col) + j] = mat[k](i, j);
					}
				}
			}
		}

		else
		{
			for (int k = 1;k <= mat.size() - 1;k++)
			{
				for (int i = 0;i <= row - 1;i++)
				{
					for (int j = 0;j <= col - 1;j++)
					{
						buf[(k*col*row) + (i*col) + j] = mat[k](j, i);
					}
				}
			}
		}

		return buf;
	}
}

void DevaFramework::setShaderUniform(
	gl::GLuint uniformid, const std::vector<mat2> &value, GLsizei count, GLboolean transpose)
{
	auto buf = packmat<float, 2, 2>(value, transpose == GL_TRUE);
	glUniformMatrix2fv(uniformid, count, transpose, &buf[0]);
}

void DevaFramework::setShaderUniform(gl::GLuint uniformid, const std::vector<mat2x3> &value, GLsizei count, GLboolean transpose)
{
	auto buf = packmat<float, 2, 3>(value, transpose == GL_TRUE);
	glUniformMatrix2fv(uniformid, count, transpose, &buf[0]);
}

void DevaFramework::setShaderUniform(gl::GLuint uniformid, const std::vector<mat2x4> &value, GLsizei count, GLboolean transpose)
{
	auto buf = packmat<float, 2, 4>(value, transpose == GL_TRUE);
	glUniformMatrix2fv(uniformid, count, transpose, &buf[0]);
}

void DevaFramework::setShaderUniform(gl::GLuint uniformid, const std::vector<mat3x2> &value, GLsizei count, GLboolean transpose)
{
	auto buf = packmat<float, 3, 2>(value, transpose == GL_TRUE);
	glUniformMatrix2fv(uniformid, count, transpose, &buf[0]);
}

void DevaFramework::setShaderUniform(gl::GLuint uniformid, const std::vector<mat3> &value, GLsizei count, GLboolean transpose)
{
	auto buf = packmat<float, 3, 3>(value, transpose == GL_TRUE);
	glUniformMatrix2fv(uniformid, count, transpose, &buf[0]);
}

void DevaFramework::setShaderUniform(gl::GLuint uniformid, const std::vector<mat3x4> &value, GLsizei count, GLboolean transpose)
{
	auto buf = packmat<float, 3, 4>(value, transpose == GL_TRUE);
	glUniformMatrix2fv(uniformid, count, transpose, &buf[0]);
}

void DevaFramework::setShaderUniform(gl::GLuint uniformid, const std::vector<mat4x2> &value, GLsizei count, GLboolean transpose)
{
	auto buf = packmat<float, 4, 2>(value, transpose == GL_TRUE);
	glUniformMatrix2fv(uniformid, count, transpose, &buf[0]);
}

void DevaFramework::setShaderUniform(gl::GLuint uniformid, const std::vector<mat4x3> &value, GLsizei count, GLboolean transpose)
{
	auto buf = packmat<float, 4, 3>(value, transpose == GL_TRUE);
	glUniformMatrix2fv(uniformid, count, transpose, &buf[0]);
}

void DevaFramework::setShaderUniform(gl::GLuint uniformid, const std::vector<mat4> &value, GLsizei count, GLboolean transpose)
{
	auto buf = packmat<float, 4, 4>(value, transpose == GL_TRUE);
	glUniformMatrix2fv(uniformid, count, transpose, &buf[0]);
}