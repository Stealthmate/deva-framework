#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_COMMON_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_COMMON_HPP

#include "Config.hpp"

#include "VulkanDeleter.hpp"
#include "VulkanInstance.hpp"
#include "VulkanPhysicalDevice.hpp"

#include <vector>

namespace DevaFramework {

	class Window;

	DEVA_FRAMEWORK_API VkShaderModule vulkanShaderFromFile(const VulkanDevice &dev, const char *filepath);
	DEVA_FRAMEWORK_API VkSurfaceKHR createSurfaceFromWindow(const VulkanInstance &vkInstance, const Window &wnd);
	DEVA_FRAMEWORK_API std::vector<uint32_t> deviceQueueFamiliesSupportSurface(const VulkanInstance &vkInstance, VkPhysicalDevice pdev, VkSurfaceKHR surface);

}

#endif //DEVA_FRAMEWORK_GRAPHICS_VULKAN_COMMON_HPP