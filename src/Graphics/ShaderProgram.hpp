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

		DEVA_API ShaderProgram(const std::vector<Shader> &shaders = std::vector<Shader>());
		DEVA_API ShaderProgram(const ShaderProgram &shaderprog) = default;
		DEVA_API ShaderProgram(ShaderProgram &&shaderprogram) = default;
		DEVA_API ShaderProgram& operator=(const ShaderProgram &shaderprog);
		DEVA_API ShaderProgram& operator=(ShaderProgram &&shaderprog);

		DEVA_API inline GLuint getHandle() const
		{
			return this->handle;
		}

		DEVA_API ShaderProgram& attachShader(const Shader &shader);
		DEVA_API ShaderProgram& detachShader(const Shader &shader);
	
	public:
		DEVA_API std::string link() const;

		DEVA_API ~ShaderProgram();

	};
}

#endif //DEVA_FRAMEWORK_GRAPHICS_SHADER_PROGRAM_H
