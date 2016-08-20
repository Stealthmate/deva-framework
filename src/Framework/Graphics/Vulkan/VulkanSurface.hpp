#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_SURFACE_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_SURFACE_HPP

#include "Config.hpp"

#include "VulkanInstance.hpp"

#include <memory>

namespace DevaFramework
{
	class VulkanSurface
	{

		std::shared_ptr<VulkanInstance> instance;
		VkSurfaceKHR surfaceHandle;


	};


}

#endif //DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_SURFACE_HPP