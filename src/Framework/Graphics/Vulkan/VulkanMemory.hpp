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

		template<> inline void destroyObject<VulkanMemory>(const VulkanDevice& dev, VulkanMemory &obj) {
			dev.vk().vkFreeMemory(dev.handle(), obj.handle(), nullptr);
			obj.reset();
		}
	}
}

#endif // DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_MEMORY_HPP