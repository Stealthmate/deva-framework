#include "VulkanBuffer.hpp"

using namespace DevaFramework;

VulkanBuffer VulkanBuffer::create(
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

	auto dev = device.handle();
	auto vk = device.vk();

	VkBuffer buf;
	VkResult result = vk.vkCreateBuffer(dev, &cinfo, nullptr, &buf);
	if (result != VK_SUCCESS) {
		throw DevaExternalFailureException("Vulkan", "Could not create buffer");
	}

	VulkanBuffer buffer(device);
	buffer.mHandle.replace(buf);

	buffer.mUsage = usage;
	buffer.mSharingMode = sharingMode;
	buffer.mSize = size;

	vk.vkGetBufferMemoryRequirements(dev, buf, &buffer.mMemoryRequirements);

	return buffer;
}

VulkanBuffer::VulkanBuffer() = default;

VulkanBuffer::VulkanBuffer(const VulkanDevice &dev) : mHandle(dev.handle(), dev.vk().vkDestroyBuffer) {}

VulkanBuffer::VulkanBuffer(VulkanBuffer &&buf)
	: mHandle(std::move(buf.mHandle)),
	mSize(buf.mSize),
	mUsage(buf.mUsage),
	mSharingMode(buf.mSharingMode),
	mMemoryRequirements(buf.mMemoryRequirements) {}

VulkanBuffer& VulkanBuffer::operator=(VulkanBuffer &&buf) {
	mHandle = std::move(buf.mHandle);
	mSize = buf.mSize;
	mUsage = buf.mUsage;
	mSharingMode = buf.mSharingMode;
	mMemoryRequirements = buf.mMemoryRequirements;

	return *this;
}

VulkanBuffer::~VulkanBuffer() = default;

void VulkanBuffer::destroy() {
	mHandle.replace();
}