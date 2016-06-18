#ifndef DEVA_FRAMEWORK_GRAPHICS_SHADER_PROGRAM_H
#define DEVA_FRAMEWORK_GRAPHICS_SHADER_PROGRAM_H

#include "Config.hpp"
#include "glTypes.hpp"

#include "Shader.hpp"
#include "ShaderVariable.hpp"

#include <vector>

namespace DevaFramework
{


	/**
		@brief A wrapper class for an OpenGL Program.
	*/
	class ShaderProgram
	{
		static const GLuint SHADERPROGRAM_HANDLE_NULL = 999999;

		GLuint handle;
		mutable std::vector<GLuint> shaders;
	public:
		///A std::string constant representing successful shader program linking
		static const std::string LINK_STATUS_OK;

	public:
		/**
			@param shaders - A list of shader objects to include in the program. Can be omitted during construction.
		*/

		DEVA_FRAMEWORK_API ShaderProgram(const std::vector<Shader> &shaders = std::vector<Shader>());

		DEVA_FRAMEWORK_API ShaderProgram(const ShaderProgram &shaderprog) = delete;
		DEVA_FRAMEWORK_API ShaderProgram& operator=(const ShaderProgram &shaderprog) = delete;

		///NOT YET IMPLEMENTED!!!
		DEVA_FRAMEWORK_API ShaderProgram(ShaderProgram &&shaderprogram);

		///NOT YET IMPLEMENTED!!!
		DEVA_FRAMEWORK_API ShaderProgram& operator=(ShaderProgram &&shaderprog);

		///@return A GLuint representing the handle to the OpenGL ProgramObject
		DEVA_FRAMEWORK_API inline GLuint getHandle() const
		{
			return this->handle;
		}

		///@param shader - a shader object to attach to the program
		DEVA_FRAMEWORK_API ShaderProgram& attachShader(const Shader &shader);
		///@param shader - a shader object to detach from the program
		DEVA_FRAMEWORK_API ShaderProgram& detachShader(GLuint shaderHandle);

		/**
		Calls glLinkProgram() on the program and returns either
		\b LINK_STATUS_OK upon successful linking or
		the OpenGL Info Log of the linking process. If the program links successfully, detaches all shader objects.
		*/
		DEVA_FRAMEWORK_API std::string link();

		template<typename T>
		DEVA_FRAMEWORK_API ShaderVariable<T> operator[](const std::string &name);

		DEVA_FRAMEWORK_API ~ShaderProgram();

	};
}

#endif //DEVA_FRAMEWORK_GRAPHICS_SHADER_PROGRAM_H
