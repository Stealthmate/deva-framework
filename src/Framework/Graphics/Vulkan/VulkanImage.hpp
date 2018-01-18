#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_IMAGE_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_IMAGE_HPP

#include "Config.hpp"
#include "VulkanObject.hpp"
#include "VulkanDevice.hpp"

namespace DevaFramework {

	struct VulkanImage {
		VkImage              handle;
		VkDeviceSize         size;
		VkBufferUsageFlags   usage;
		VkSharingMode        sharingMode;
		VkMemoryRequirements mMemoryRequirements;
	};

	namespace Vulkan {
		template<> inline void destroyObject<VulkanImage>(const VulkanDevice &dev, VulkanImage &obj) {
			dev.vk.vkDestroyImage(dev.handle, obj.handle, nullptr);
			obj.handle = VK_NULL_HANDLE;
		}
	}
}

#endif //DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_IMAGE_HPP