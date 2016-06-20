#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_DEVICE_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_DEVICE_HPP

#include "Config.hpp"

#include "VulkanPhysicalDevice.hpp"

namespace DevaFramework
{

	class VulkanDevice
	{

		VkDevice handle;

	public:

		DEVA_FRAMEWORK_API VulkanDevice(const VulkanPhysicalDevice &physicalDevice, const VkDeviceCreateInfo &info);

	};

}

#endif //DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_DEVICE_HPP