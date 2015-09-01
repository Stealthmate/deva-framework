#ifndef DEVA_FRAMEWORK_GRAPHICS_SHADER_H
#define DEVA_FRAMEWORK_GRAPHICS_SHADER_H

#include "Config.hpp"

#include "glTypes.hpp"
#include <string>


namespace DevaFramework
{
	USE_GL;
	class Shader
	{

		static const GLuint SHADER_HANDLE_NULL = 999999;

		GLuint handle;
		std::string source;
		GLenum shaderType;

	public:
		
		static std::string const COMPILE_STATUS_OK;

		DEVA_API Shader(GLenum shaderType, const std::string &source = "");
		DEVA_API Shader(const Shader &shader) = default;
		DEVA_API Shader(Shader &&shader) = default;
		DEVA_API Shader& operator=(const Shader &shader);
		DEVA_API Shader& operator=(Shader &&shader);

		DEVA_API inline GLuint getHandle() const
		{
			return this->handle;
		}

		DEVA_API void setSource(const std::string &source);

		DEVA_API std::string compile() const;

		DEVA_API ~Shader();

	};

}

#endif //DEVA_FRAMEWORK_GRAPHICS_SHADER_H
