#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_COMMAND_POOL_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_COMMAND_POOL_HPP

#include "Config.hpp"

#include "VulkanDevice.hpp"
#include "VulkanHandle.hpp"
#include "VulkanObject.hpp"

namespace DevaFramework {

	typedef VulkanObject<VkCommandPool, VkCommandPoolCreateInfo> VulkanCommandPool;
	typedef VulkanObject<VkCommandBuffer, VkCommandBufferAllocateInfo> VulkanCommandBuffer;

	namespace Vulkan {

		DEVA_FRAMEWORK_API VulkanCommandPool createCommandPool(const VulkanDevice &dev, uint32_t queue, VkCommandPoolCreateFlags flags = 0);

		DEVA_FRAMEWORK_API VulkanCommandBuffer allocateCommandBuffer(
			const VulkanDevice &dev,
			const VulkanCommandPool &cpool,
			VkCommandBufferLevel level);

		DEVA_FRAMEWORK_API std::vector<VulkanCommandBuffer> allocateCommandBuffers(
			const VulkanDevice &dev,
			const VulkanCommandPool &cpool,
			VkCommandBufferLevel level,
			uint32_t count);

		template <> inline void destroyObject(const VulkanDevice &dev, VulkanCommandPool &obj) {
			dev.vk().vkDestroyCommandPool(dev.handle(), obj.handle(), nullptr);
			obj.reset();
		}

	}
}

#endif // DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_COMMAND_POOL_HPP