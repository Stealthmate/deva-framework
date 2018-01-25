#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_MEMORY_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_MEMORY_HPP

#include "Config.hpp"

namespace DevaFramework {

	struct VulkanDevice;
	struct VulkanImage;
	struct VulkanBuffer;

	struct VulkanMemory {
		VkDeviceMemory handle;
		VkDeviceSize size;
		VkMemoryType type;
		uint32_t typeIndex;
	};

	namespace Vulkan {

		DEVA_FRAMEWORK_API uint32_t findMemoryTypeIndex(const VkPhysicalDeviceMemoryProperties &pdevMemProp, uint32_t typeBits, VkMemoryPropertyFlags properties);

		DEVA_FRAMEWORK_API VulkanMemory allocateMemory(VkDeviceSize size, uint32_t allocInfo);
		DEVA_FRAMEWORK_API VulkanMemory allocateMemoryForBuffer(const VulkanDevice &dev, const VulkanBuffer &buffer, VkMemoryPropertyFlags properties);
		DEVA_FRAMEWORK_API VulkanMemory allocateMemoryForImage(const VulkanDevice &dev, const VulkanImage &image, VkMemoryPropertyFlags properties);

		DEVA_FRAMEWORK_API void destroyObject(const VulkanDevice& dev, VulkanMemory &obj);
	}
}

#endif // DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_MEMORY_HPP