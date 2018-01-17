#include "VulkanCommandPool.hpp"

using namespace DevaFramework;

std::vector<VulkanCommandBuffer> Vulkan::allocateCommandBuffers(
	const VulkanDevice &device,
	const VulkanCommandPool &cpool,
	VkCommandBufferLevel level,
	uint32_t count) {

	auto dev = device.handle();
	auto vk = device.vk();

	std::vector<VulkanCommandBuffer> cbufs;

	VkCommandBufferAllocateInfo info;
	info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	info.pNext = nullptr;
	info.level = level;
	info.commandPool = cpool.handle();
	info.commandBufferCount = count;

	VkResult res;
	std::vector<VkCommandBuffer> cbufhandles;
	cbufhandles.resize(count);
	res = vk.vkAllocateCommandBuffers(dev, &info, cbufhandles.data());
	if (res != VK_SUCCESS) {
		throw DevaException("Could not allocate command buffers");
	}

	for (auto b : cbufhandles) {
		cbufs.push_back({ b, info });
	}

	return cbufs;
}

VulkanCommandBuffer Vulkan::allocateCommandBuffer(
	const VulkanDevice &device,
	const VulkanCommandPool &cpool,
	VkCommandBufferLevel level) {

	return std::move(allocateCommandBuffers(device, cpool, level, 1)[0]);

}

VulkanCommandPool Vulkan::createCommandPool(const VulkanDevice &dev, uint32_t queueFamily, VkCommandPoolCreateFlags flags) {
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

	return VulkanCommandPool(handle, cinfo);
}