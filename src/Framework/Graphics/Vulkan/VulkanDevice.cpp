#include "VulkanDevice.hpp"

#include "../../Exceptions.hpp"

using namespace DevaFramework;

VulkanDevice::VulkanDevice(const VulkanPhysicalDevice &physicalDevice, const VkDeviceCreateInfo &deviceInfo)
{
	auto err = vkCreateDevice(physicalDevice.getHandle(), &deviceInfo, NULL, &handle);
	if (err != VK_SUCCESS)
		throw DevaFailureException(
			"Could not create Vulkan device",
			"vkCreateDevice(physicalDevice.getHandle(), &deviceInfo, NULL, &handle)",
			"VulkanDevice::VulkanDevice(const VulkanPhysicalDevice &physicalDevice, const VkDeviceCreateInfo &deviceInfo)");
}