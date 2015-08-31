#ifndef DEVA_FRAMEWORK_GRAPHICS_WINDOW_CONFIG_H
#define DEVA_FRAMEWORK_GRAPHICS_WINDOW_CONFIG_H

#include "../Config.hpp"

struct GLFWwindow;

namespace DevaFramework
{

typedef GLFWwindow* Window_Handle;
const Window_Handle WINDOW_HANDLE_NULL = nullptr;

}

#endif // DEVA_FRAMEWORK_GRAPHICS_WINDOW_CONFIG_H
