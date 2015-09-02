#ifndef DEVA_FRAMEWORK_GRAPHICS_OPENGL_COMMON_H
#define DEVA_FRAMEWORK_GRAPHICS_OPENGL_COMMON_H

#include "Config.hpp"

#include <glbinding/gl/gl.h>

#include <string>

namespace DevaFramework
{

	DEVA_GRAPHICS_API gl::GLuint loadShaderSet(std::string VertexShaderCode, std::string FragmentShaderCode);


}

#endif // DEVA_FRAMEWORK_GRAPHICS_OPENGL_COMMON_H
