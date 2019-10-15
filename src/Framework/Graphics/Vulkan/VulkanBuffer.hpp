#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_BUFFER_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_BUFFER_HPP

#include "Config.hpp"

namespace DevaFramework {

	struct VulkanDevice;

	struct VulkanBuffer {
		VkBuffer              handle;
		VkDeviceSize          size;
		VkBufferUsageFlags    usage;
		VkSharingMode         sharingMode;
		VkMemoryRequirements  memoryRequirements;
	};

	namespace Vulkan {
		DEVA_FRAMEWORK_API VulkanBuffer createBuffer(
			const VulkanDevice &dev,
			VkBufferCreateFlags flags,
			VkDeviceSize size,
			VkBufferUsageFlags usage,
			VkSharingMode sharingMode,
			const std::vector<uint32_t> &queues = std::vector<uint32_t>());
		
		DEVA_FRAMEWORK_API void destroyObject(const VulkanDevice& dev, VulkanBuffer &obj);
	}
}

#endif // DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_BUFFER_HPP