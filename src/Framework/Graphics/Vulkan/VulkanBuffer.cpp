#include "VulkanBuffer.hpp"

#include "VulkanDevice.hpp"
#include "VulkanDeviceFunctionSet.hpp"

using namespace DevaFramework;

VulkanBuffer Vulkan::createBuffer(
	const VulkanDevice &device,
	VkBufferCreateFlags flags,
	VkDeviceSize size,
	VkBufferUsageFlags usage,
	VkSharingMode sharingMode,
	const std::vector<uint32_t> &queues)
{
	VkBufferCreateInfo cinfo;
	cinfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	cinfo.pNext = nullptr;
	cinfo.flags = flags;
	cinfo.size = size;
	cinfo.usage = usage;
	cinfo.sharingMode = sharingMode;
	cinfo.queueFamilyIndexCount = static_cast<uint32_t>(queues.size());
	cinfo.pQueueFamilyIndices = queues.size() > 0 ? queues.data() : nullptr;

	auto dev = device.handle;
	auto vk = device.vk;

	VkBuffer handle;

	VkResult result = vk.vkCreateBuffer(dev, &cinfo, nullptr, &handle);
	if (result != VK_SUCCESS) {
		throw DevaExternalFailureException("Vulkan", "Could not create buffer");
	}
	VkMemoryRequirements memreq;
	vk.vkGetBufferMemoryRequirements(dev, handle, &memreq);

	return VulkanBuffer{ handle, size, usage, sharingMode, memreq };
}

void DevaFramework::Vulkan::destroyObject(const VulkanDevice &dev, VulkanBuffer &buf) {
	dev.vk.vkDestroyBuffer(dev.handle, buf.handle, nullptr);
}