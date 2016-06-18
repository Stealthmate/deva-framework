namespace
{
	template<typename T, unsigned int size>
	std::vector<T> packvec(const std::vector<BaseVector<T, size>>& vec)
	{
		std::vector<T> buf(size*vec.size());
		for (int i = 0;i <= vec.size() - 1;i++)
		{
			for (int j = 0;j <= size - 1;j++)
			{
				buf[i*size + j] = vec[i][j];
			}
		}
		return buf;
	}
}

//vec2
void DevaFramework::setShaderUniform(gl::GLuint uniformid, const vec2 &value, GLsizei count, GLboolean transpose)
{
	glUniform2f(uniformid, value[0], value[1]);
}

void DevaFramework::setShaderUniform(gl::GLuint uniformid, const std::vector<vec2> &value, GLsizei count, GLboolean transpose)
{
	auto buf = packvec<float, 2>(value);
	glUniform2fv(uniformid, count, &buf[0]);
}

//ivec2
void DevaFramework::setShaderUniform(gl::GLuint uniformid, const ivec2 &value, GLsizei count, GLboolean transpose)
{
	glUniform2i(uniformid, value[0], value[1]);
}

void DevaFramework::setShaderUniform(gl::GLuint uniformid, const std::vector<ivec2> &value, GLsizei count, GLboolean transpose)
{
	auto buf = packvec<int, 2>(value);
	glUniform2iv(uniformid, count, &buf[0]);
}

//uvec2
void DevaFramework::setShaderUniform(gl::GLuint uniformid, const uvec2 &value, GLsizei count, GLboolean transpose)
{
	glUniform2i(uniformid, value[0], value[1]);
}

void DevaFramework::setShaderUniform(gl::GLuint uniformid, const std::vector<uvec2> &value, GLsizei count, GLboolean transpose)
{
	auto buf = packvec<unsigned int, 2>(value);
	glUniform2uiv(uniformid, count, &buf[0]);
}

//vec3
void DevaFramework::setShaderUniform(gl::GLuint uniformid, const vec3 &value, GLsizei count, GLboolean transpose)
{
	glUniform3f(uniformid, value[0], value[1], value[2]);
}

void DevaFramework::setShaderUniform(gl::GLuint uniformid, const std::vector<vec3> &value, GLsizei count, GLboolean transpose)
{
	auto buf = packvec<float, 3>(value);
	glUniform3fv(uniformid, count, &buf[0]);
}

//ivec3
void DevaFramework::setShaderUniform(gl::GLuint uniformid, const ivec3 &value, GLsizei count, GLboolean transpose)
{
	glUniform3i(uniformid, value[0], value[1], value[2]);
}

void DevaFramework::setShaderUniform(gl::GLuint uniformid, const std::vector<ivec3> &value, GLsizei count, GLboolean transpose)
{
	auto buf = packvec<int, 3>(value);
	glUniform3iv(uniformid, count, &buf[0]);
}

//uvec3
void DevaFramework::setShaderUniform(gl::GLuint uniformid, const uvec3 &value, GLsizei count, GLboolean transpose)
{
	glUniform3i(uniformid, value[0], value[1], value[2]);
}

void DevaFramework::setShaderUniform(gl::GLuint uniformid, const std::vector<uvec3> &value, GLsizei count, GLboolean transpose)
{
	auto buf = packvec<unsigned int, 3>(value);
	glUniform3uiv(uniformid, count, &buf[0]);
}

//vec4
void DevaFramework::setShaderUniform(gl::GLuint uniformid, const vec4 &value, GLsizei count, GLboolean transpose)
{
	glUniform4f(uniformid, value[0], value[1], value[2], value[3]);
}

void DevaFramework::setShaderUniform(gl::GLuint uniformid, const std::vector<vec4> &value, GLsizei count, GLboolean transpose)
{
	auto buf = packvec<float, 4>(value);
	glUniform4fv(uniformid, count, &buf[0]);
}

//ivec4
void DevaFramework::setShaderUniform(gl::GLuint uniformid, const ivec4 &value, GLsizei count, GLboolean transpose)
{
	glUniform4i(uniformid, value[0], value[1], value[2], value[3]);
}

void DevaFramework::setShaderUniform(gl::GLuint uniformid, const std::vector<ivec4> &value, GLsizei count, GLboolean transpose)
{
	auto buf = packvec<int, 4>(value);
	glUniform4iv(uniformid, count, &buf[0]);
}

//uvec4
void DevaFramework::setShaderUniform(gl::GLuint uniformid, const uvec4 &value, GLsizei count, GLboolean transpose)
{
	glUniform4i(uniformid, value[0], value[1], value[2], value[3]);
}

void DevaFramework::setShaderUniform(gl::GLuint uniformid, const std::vector<uvec4> &value, GLsizei count, GLboolean transpose)
{
	auto buf = packvec<unsigned int, 4>(value);
	glUniform4uiv(uniformid, count, &buf[0]);
}