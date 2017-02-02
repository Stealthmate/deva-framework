#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_DEVICE_BUILDER_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_DEVICE_BUILDER_HPP

#include "Config.hpp"
#include "VulkanDevice.hpp"

#include <unordered_map>

namespace DevaFramework
{
	class VulkanDeviceBuilder {
		VkQueueFlags mQueueSupport;
		std::unordered_map<uint32_t, uint32_t> queues;

	public:

		DEVA_FRAMEWORK_API VulkanDeviceBuilder(const VulkanPhysicalDeviceWrapper &pdev);

		DEVA_FRAMEWORK_API VulkanDeviceBuilder& useQueueFamily(uint32_t familyIndex, uint32_t count);
		DEVA_FRAMEWORK_API VulkanDeviceBuilder& 

	};
}

#endif //DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_DEVICE_BUILDER_HPP