#include "VulkanCommandPool.hpp"

#include "VulkanDevice.hpp"
#include <unordered_map>

using namespace DevaFramework;

std::vector<VulkanCommandBuffer> Vulkan::allocateCommandBuffers(
	const VulkanDevice &device,
	const VulkanCommandPool &cpool,
	VkCommandBufferLevel level,
	uint32_t count) {

	auto dev = device.handle;
	auto &vk = device.vk;

	std::vector<VulkanCommandBuffer> cbufs;

	VkCommandBufferAllocateInfo info;
	info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	info.pNext = nullptr;
	info.level = level;
	info.commandPool = cpool.handle;
	info.commandBufferCount = count;

	VkResult res;
	std::vector<VkCommandBuffer> cbufhandles;
	cbufhandles.resize(count);
	res = vk.vkAllocateCommandBuffers(dev, &info, cbufhandles.data());
	if (res != VK_SUCCESS) {
		throw DevaException("Could not allocate command buffers");
	}

	for (auto b : cbufhandles) {
		VulkanCommandBuffer buf;
		buf.handle = b;
		buf.level = info.level;
		buf.commandPool = cpool;
		cbufs.push_back(buf);
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

	VulkanCommandPool pool;

	VkCommandPoolCreateInfo cinfo = {};
	cinfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	cinfo.queueFamilyIndex = queueFamily;
	cinfo.flags = flags; // Optional
	auto device = dev.handle;
	auto vk = dev.vk;

	VkResult result = vk.vkCreateCommandPool(device, &cinfo, nullptr, &pool.handle);
	if (result != VK_SUCCESS) {
		throw DevaException("Could not create CommandPool!");
	}

	pool.flags = flags;
	pool.queueFamilyIndex = queueFamily;

	return pool;
}

void Vulkan::freeCommandBuffers(const VulkanDevice &dev, const std::vector<VulkanCommandBuffer> &buffers) {
	auto handle = dev.handle;
	auto vk = dev.vk;

	std::unordered_map<VkCommandPool, std::vector<VkCommandBuffer>> poolmap;

	for (auto &b : buffers) {
		auto &pv = poolmap.find(b.commandPool.handle);
		if (pv != poolmap.end()) {
			pv->second.push_back(b.handle);
		} else {
			poolmap.insert({ b.commandPool.handle, {b.handle} });
		}
	}

	for (auto &p : poolmap) {
		vk.vkFreeCommandBuffers(handle, p.first, p.second.size(), p.second.data());
	}
}

void Vulkan::beginCommandBuffer(const VulkanDevice &dev, VkCommandBuffer buffer, VkCommandBufferUsageFlags usage) {
	VkCommandBufferBeginInfo info;
	info.flags = usage;
	info.pInheritanceInfo = nullptr;
	info.pNext = nullptr;
	info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	dev.vk.vkBeginCommandBuffer(buffer, &info);
}

void Vulkan::destroyObject(const VulkanDevice &dev, VulkanCommandPool &pool) {
	dev.vk.vkDestroyCommandPool(dev.handle, pool.handle, nullptr);
	pool.handle = VK_NULL_HANDLE;
}