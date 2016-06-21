#include "VulkanDevice.hpp"

#include <Deva/Exceptions.hpp>

using namespace DevaFramework;
using namespace DevaEngine;

VulkanDevice::VulkanDevice(const VulkanPhysicalDevice &physicalDevice, const VkDeviceCreateInfo &deviceInfo)
{
	auto err = vkCreateDevice(physicalDevice, &deviceInfo, NULL, &deviceHandle);
	if (err != VK_SUCCESS)
		throw DevaFailureException(
			"Failed to create Vulkan logical device",
			"vkCreateDevice(physicalDevice, &deviceInfo, NULL, &deviceHandle)",
			"VulkanDevice::VulkanDevice(const VkPhysicalDevice &physicalDevice, const VkDeviceCreateInfo &deviceInfo)");
}