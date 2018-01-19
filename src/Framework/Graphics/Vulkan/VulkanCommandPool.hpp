#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_COMMAND_POOL_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_COMMAND_POOL_HPP

#include "Config.hpp"

#include "VulkanDevice.hpp"
#include "VulkanHandle.hpp"
#include "VulkanObject.hpp"

namespace DevaFramework {

	struct VulkanCommandPool {
		VkCommandPool handle;
		VkCommandPoolCreateFlags flags;
		uint32_t queueFamilyIndex;
	};

	struct VulkanCommandBuffer {
		VkCommandBuffer handle;
		VulkanCommandPool commandPool;
		VkCommandBufferLevel level;
	};

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

		DEVA_FRAMEWORK_API void freeCommandBuffers(const VulkanDevice &dev, const std::vector<VulkanCommandBuffer> &buffers);

		DEVA_FRAMEWORK_API void beginCommandBuffer(const VulkanDevice &dev, VkCommandBuffer buffer, VkCommandBufferUsageFlags flags);

		DEVA_FRAMEWORK_API void submitSingleBuffer(const VulkanDevice &dev, VkQueue queue, VkCommandBuffer buffer);


		template <> inline void destroyObject(const VulkanDevice &dev, VulkanCommandPool &obj) {
			dev.vk.vkDestroyCommandPool(dev.handle, obj.handle, nullptr);
			obj.handle = VK_NULL_HANDLE;
		}

	}
}

#endif // DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_COMMAND_POOL_HPP