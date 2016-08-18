#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_SURFACE_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_SURFACE_HPP

#include "Config.hpp"

#include "../../Window/Window.hpp"

namespace DevaFramework
{
	class Surface
	{
		VkSurfaceKHR handle;
	public:
		DEVA_FRAMEWORK_API Surface(const Window &wnd);
	};
}


#endif //DEVA_FRAMEWORK_GRAPHICS_VULKAN_SURFACE_HPP