#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_IMAGE_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_IMAGE_HPP

#include "Config.hpp"
#include "VulkanObject.hpp"
#include "VulkanDevice.hpp"

namespace DevaFramework {

	struct VulkanBufferInfo {
		VkDeviceSize           size;
		VkBufferUsageFlags     usage;
		VkSharingMode          sharingMode;
		VkMemoryRequirements mMemoryRequirements;
	};

	typedef VulkanObject<VkBuffer, VulkanBufferInfo> VulkanBuffer;

	namespace Vulkan {
		DEVA_FRAMEWORK_API VulkanBuffer createBuffer(
			const VulkanDevice &dev,
			VkBufferCreateFlags flags,
			VkDeviceSize size,
			VkBufferUsageFlags usage,
			VkSharingMode sharingMode,
			const std::vector<uint32_t> &queues = std::vector<uint32_t>());
	}
}

#endif //DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_IMAGE_HPP