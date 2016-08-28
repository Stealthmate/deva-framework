#include "VulkanDevice.hpp"

#include "../../Exceptions.hpp"

using namespace DevaFramework;

VulkanDevice::VulkanDevice() = default;

VulkanDevice::VulkanDevice(VkDevice dev, const VulkanInstance &vkinstance) : handle(dev)
{
	vk.load(dev, vkinstance);
}