#ifndef DEVA_FRAMEWORK_GRAPHICS_SHADER_PROGRAM_H
#define DEVA_FRAMEWORK_GRAPHICS_SHADER_PROGRAM_H

#include "Config.hpp"
#include "glTypes.hpp"

#include "Shader.hpp"

#include <vector>

namespace DevaFramework
{
	USE_GL;
	class ShaderProgram
	{
		
		static const GLuint SHADERPROGRAM_HANDLE_NULL = 999999;
	public:
		static const std::string LINK_STATUS_OK;

	private:
		GLuint handle;
		std::vector<GLuint> shaders;
		


	public:

		DEVA_GRAPHICS_API ShaderProgram(const std::vector<Shader> &shaders = std::vector<Shader>());
		DEVA_GRAPHICS_API ShaderProgram(const ShaderProgram &shaderprog) = default;
		DEVA_GRAPHICS_API ShaderProgram(ShaderProgram &&shaderprogram) = default;
		DEVA_GRAPHICS_API ShaderProgram& operator=(const ShaderProgram &shaderprog);
		DEVA_GRAPHICS_API ShaderProgram& operator=(ShaderProgram &&shaderprog);

		DEVA_GRAPHICS_API inline GLuint getHandle() const
		{
			return this->handle;
		}

		DEVA_GRAPHICS_API ShaderProgram& attachShader(const Shader &shader);
		DEVA_GRAPHICS_API ShaderProgram& detachShader(const Shader &shader);
	
	public:
		DEVA_GRAPHICS_API std::string link() const;

		DEVA_GRAPHICS_API ~ShaderProgram();

	};
}

#endif //DEVA_FRAMEWORK_GRAPHICS_SHADER_PROGRAM_H
