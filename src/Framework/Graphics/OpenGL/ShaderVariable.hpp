#ifndef DEVA_FRAMEWORK_GRAPHICS_SHADER_VARIABLE_H
#define DEVA_FRAMEWORK_GRAPHICS_SHADER_VARIABLE_H

#include "Config.hpp"
#include "glTypes.hpp"

#include "Common.hpp"
namespace DevaFramework
{

	


	template <typename T>
	class ShaderVariable
	{
		std::string name;
		GLuint id;
		T data;
		size_t arr_size;

	public:

		ShaderVariable();
		ShaderVariable(const std::string &name, GLuint progid);

		void setValue(const T& data) { setUniformValue(id, data); }
		void setValue(const std::vector<T> &data, GLsizei count = 1) { setUniformValue(id, data, count); }
		template<typename mattype, int i, int j>
		void setValue(const BaseMatrix<mattype, i, j> &data, GLsizei count = 1, GLboolean transpose = GL_FALSE) 
		{
			setUniformValue(id, data, count, transpose);
		}


	};
}


#endif //DEVA_FRAMEWORK_GRAPHICS_SHADER_VARIABLE_H