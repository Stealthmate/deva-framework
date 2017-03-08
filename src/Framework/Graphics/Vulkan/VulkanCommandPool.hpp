#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_COMMAND_POOL_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_COMMAND_POOL_HPP

#include "Config.hpp"

#include "VulkanDevice.hpp"
#include "VulkanHandle.hpp"

namespace DevaFramework {
	class VulkanCommandPool : public VulkanHandle<VkCommandPool> {
		VkCommandPoolCreateFlags flags;

		VulkanCommandPool(const VulkanDevice &dev) 
			: VulkanHandle<VkCommandPool>(dev.handle(), dev.vk().vkDestroyCommandPool), 
			flags(0) {}

	public:

		DEVA_FRAMEWORK_API VulkanCommandPool() : flags(0) {}

		DEVA_FRAMEWORK_API VulkanCommandPool(const VulkanDevice &dev, uint32_t queue, VkCommandPoolCreateFlags flags = 0);
	};
}

#endif // DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_COMMAND_POOL_HPP