#ifndef DEVA_FRAMEWORK_GRAPHICS_SHADER_H
#define DEVA_FRAMEWORK_GRAPHICS_SHADER_H

#include "Config.hpp"

#include "glTypes.hpp"
#include <string>


namespace DevaFramework
{
	USE_GL;

	/**
		@brief A wrapper class for an OpenGL Shader
	*/
	class Shader
	{
		static const GLuint SHADER_HANDLE_NULL = 999999;

		GLuint handle;
		std::string source;
		GLenum shaderType;

	public:
		
		///A std::string constant representing successful shader compilation
		static const std::string COMPILE_STATUS_OK;

		/**
			@param shaderType - the type of shader to be constructed. Can be any of the shader types
			specified by OpenGL
			
			@param source - the source code of the shader. Can be omitted during construction.
		*/
		DEVA_FRAMEWORK_API Shader(GLenum shaderType, const std::string &source = "");
	
		DEVA_FRAMEWORK_API Shader(const Shader &shader) = delete;

		/**
			Obtains ownership of the OpenGL ShaderObject
			associated with, and thus invalidates \b shader.
		*/
		DEVA_FRAMEWORK_API Shader(Shader &&shader);
		
		DEVA_FRAMEWORK_API Shader& operator=(const Shader &shader) = delete;

		/**
			Calls glDeleteShader() on the current shader and obtains ownership of the OpenGL ShaderObject
			associated with, and thus invalidates \b shader.
		*/
		DEVA_FRAMEWORK_API Shader& operator=(Shader &&shader);

		///@return A GLuint representing the handle to the OpenGL shader object
		DEVA_FRAMEWORK_API inline GLuint getHandle() const
		{
			return this->handle;
		}

		///(Re)sets the shader source code. @param source - the (new) source code of the shader
		DEVA_FRAMEWORK_API void setSource(const std::string &source);

		/**
			Calls glCompileShader() on the shader and returns either 
			\b COMPILE_STATUS_OK upon successful compilation or
			the OpenGL Info Log of the compilation process
		*/
		DEVA_FRAMEWORK_API std::string compile() const;

		DEVA_FRAMEWORK_API ~Shader();
	};

}

#endif //DEVA_FRAMEWORK_GRAPHICS_SHADER_H
