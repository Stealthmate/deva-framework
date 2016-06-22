#ifndef DEVA_ENGINE_VULKAN_DEVICE_HPP
#define DEVA_ENGINE_VULKAN_DEVICE_HPP

#include "Config.hpp"

#include <vulkan/vulkan.h>
#include <Deva/Graphics/VulkanPhysicalDevice.hpp>

namespace DevaEngine
{
	class VulkanDevice
	{

		VkDevice deviceHandle;

	public:
		DEVA_ENGINE_API VulkanDevice(const VulkanPhysicalDevice &physicalDevice, const VkDeviceCreateInfo &createinfo);
	};
}

#endif //DEVA_ENGINE_VULKAN_DEVICE_HPP