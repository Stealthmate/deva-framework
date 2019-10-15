#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_DEVICE_QUEUE_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_DEVICE_QUEUE_HPP

#include "Config.hpp"

namespace DevaFramework
{
	struct VulkanQueue {
		VkQueue handle;
		VkDevice parentDevice;
		uint32_t familyIndex;
		uint32_t index;
		VkQueueFlags type;
		float priority;
	};
}

#endif //DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_DEVICE_QUEUE_HPP
