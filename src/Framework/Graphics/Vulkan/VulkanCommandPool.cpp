#include "VulkanCommandPool.hpp"

using namespace DevaFramework;

VulkanCommandPool::VulkanCommandPool(const VulkanDevice &dev, uint32_t queueFamily, VkCommandPoolCreateFlags flags) : VulkanCommandPool(dev) {
	VkCommandPoolCreateInfo cinfo = {};
	cinfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	cinfo.queueFamilyIndex = queueFamily;
	cinfo.flags = flags; // Optional
	auto device = dev.handle();
	auto vk = dev.vk();
	VkCommandPool handle;
	VkResult result = vk.vkCreateCommandPool(device, &cinfo, nullptr, &handle);
	if (result != VK_SUCCESS) {
		throw DevaException("Could not create CommandPool!");
	}

	this->replace(handle);
}