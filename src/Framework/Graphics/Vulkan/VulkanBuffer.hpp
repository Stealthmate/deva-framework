#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_BUFFER_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_BUFFER_HPP

#include "Config.hpp"
#include "VulkanHandle.hpp"

namespace DevaFramework {

	class VulkanBuffer : public VulkanHandle<VkBuffer> {

		static VulkanBuffer deepCopy(const VulkanBuffer &buffer);

		const VkBufferUsageFlagBits usage;
		const VkSharingMode sharingMode;

		VulkanBuffer(const VulkanDevice &dev);
		VulkanBuffer(const VulkanBuffer& buffer) = delete;
		VulkanBuffer(VulkanBuffer &&buffer);
		VulkanBuffer& operator=(const VulkanBuffer &buffer) = delete;
		VulkanBuffer& operator=(VulkanBuffer &&buffer) = delete;
		~VulkanBuffer();
	};

}

#endif // DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_BUFFER_HPP