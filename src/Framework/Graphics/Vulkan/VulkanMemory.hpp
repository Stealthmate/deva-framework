#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_MEMORY_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_MEMORY_HPP

#include "Config.hpp"
#include "VulkanObject.hpp"
#include "VulkanBuffer.hpp"

namespace DevaFramework {

	struct VulkanMemoryInfo {
		VkDeviceSize size;
		VkMemoryType type;
		uint32_t typeIndex;
	};

	typedef VulkanObject<VkDeviceMemory, VulkanMemoryInfo> VulkanMemory;

	namespace Vulkan {
		DEVA_FRAMEWORK_API VulkanMemory allocateMemory(VkDeviceSize size, uint32_t allocInfo);
		DEVA_FRAMEWORK_API VulkanMemory allocateMemoryForBuffer(const VulkanBuffer &buffer, const VulkanDevice &dev, VkMemoryPropertyFlags properties);
	}
}

#endif // DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_MEMORY_HPP