#ifndef DEVA_FRAMEWORK_GRAPHICS_WINDOW_CONFIG_H
#define DEVA_FRAMEWORK_GRAPHICS_WINDOW_CONFIG_H

#include "../Config.hpp"

#ifdef _WIN32
	#ifdef DEVA_BUILD_WINDOW
		#ifdef DEVA_BUILD_SHARED
			#define DEVA_WINDOW_API __declspec(dllexport)
		#else
			#define DEVA_WINDOW_API __declspec(dllimport)
		#endif
	#else
		#define DEVA_WINDOW_API
	#endif
#endif

struct GLFWwindow;

namespace DevaFramework
{

typedef GLFWwindow* Window_Handle;
const Window_Handle WINDOW_HANDLE_NULL = nullptr;

}

#endif // DEVA_FRAMEWORK_GRAPHICS_WINDOW_CONFIG_H
