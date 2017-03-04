#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_COMMON_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_COMMON_HPP

#include "Config.hpp"

#include "VulkanDeleter.hpp"
#include "VulkanInstance.hpp"
#include "VulkanPhysicalDevice.hpp"


#include "../VertexBuffer.hpp"

#include <vector>

namespace DevaFramework {

	class Window;
	namespace Vulkan
	{
		DEVA_FRAMEWORK_API VkShaderModule loadShaderFromFile(const VulkanDevice &dev, const char *filepath);
		DEVA_FRAMEWORK_API VkSurfaceKHR createSurfaceFromWindow(const VulkanInstance &vkInstance, const Window &wnd);
		DEVA_FRAMEWORK_API std::vector<uint32_t> deviceQueueFamiliesSupportSurface(const VulkanInstance &vkInstance, VkPhysicalDevice pdev, VkSurfaceKHR surface);
		DEVA_FRAMEWORK_API std::vector<VkVertexInputAttributeDescription> getAttributeDescriptionsForVertexBuffer(
			const VertexBuffer &vb, 
			const std::vector<uint32_t> &locations);
	}

}

#endif //DEVA_FRAMEWORK_GRAPHICS_VULKAN_COMMON_HPP