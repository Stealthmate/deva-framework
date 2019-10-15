#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_MEMORY_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_MEMORY_HPP

#include "Config.hpp"

namespace DevaFramework {

	struct VulkanDevice;
	struct VulkanImage;
	struct VulkanBuffer;

	struct VulkanMemoryAlloc {
		VkDeviceMemory handle;
		VkDeviceSize size;
		VkMemoryType type;
		uint32_t typeIndex;
	};

	struct VulkanMemoryRange {
		VkDeviceMemory memory;
		VkDeviceSize offset;
		VkDeviceSize size;
	};

	class IVulkanMemoryManager {
	public:
		virtual std::shared_ptr<const VulkanMemoryRange> allocate(
			const VkMemoryRequirements &reqs,
			VkMemoryPropertyFlags properties) = 0;
		virtual void free(VulkanMemoryRange &range) = 0;
	};

	namespace Vulkan {

		DEVA_FRAMEWORK_API uint32_t findMemoryTypeIndex(const VkPhysicalDeviceMemoryProperties &pdevMemProp, uint32_t typeBits, VkMemoryPropertyFlags properties);

		DEVA_FRAMEWORK_API VulkanMemoryAlloc allocateMemory(VkDeviceSize size, uint32_t allocInfo);
		DEVA_FRAMEWORK_API VulkanMemoryAlloc allocateMemoryForBuffer(const VulkanDevice &dev, const VulkanBuffer &buffer, VkMemoryPropertyFlags properties);
		DEVA_FRAMEWORK_API VulkanMemoryAlloc allocateMemoryForImage(const VulkanDevice &dev, const VulkanImage &image, VkMemoryPropertyFlags properties);

		DEVA_FRAMEWORK_API void destroyObject(const VulkanDevice& dev, VulkanMemoryAlloc &obj);
	}
}

#endif // DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_MEMORY_HPP