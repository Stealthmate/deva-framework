#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_BUFFER_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_BUFFER_HPP

#include "Config.hpp"
#include "VulkanHandle.hpp"
#include "VulkanObject.hpp"
#include "VulkanDevice.hpp"

namespace DevaFramework {

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
		
		template<> inline void destroyObject<VulkanBuffer>(const VulkanDevice& dev, VulkanBuffer &obj) {
			dev.vk.vkDestroyBuffer(dev.handle, obj.handle, nullptr);
			obj.handle = VK_NULL_HANDLE;
		}
	}
}

#endif // DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_BUFFER_HPP