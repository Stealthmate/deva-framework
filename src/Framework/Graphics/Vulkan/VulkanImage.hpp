#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_IMAGE_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_IMAGE_HPP

#include "Config.hpp"

namespace DevaFramework {

	struct VulkanDevice;

	struct VulkanImage {
		VkImage              handle;
		VkDeviceSize         size;
		VkBufferUsageFlags   usage;
		VkSharingMode        sharingMode;
		VkMemoryRequirements mMemoryRequirements;
	};

	namespace Vulkan {
		DEVA_FRAMEWORK_API void destroyObject(const VulkanDevice &dev, VulkanImage &obj);
	}
}

#endif //DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_IMAGE_HPP