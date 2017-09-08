#include "VulkanMemory.hpp"

using namespace DevaFramework;

VulkanMemory VulkanMemory::forBuffer(const VulkanBuffer &buffer, const VulkanDevice &dev, VkMemoryPropertyFlags properties) {
	VkMemoryAllocateInfo allocInfo;
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.pNext = nullptr;
	allocInfo.allocationSize = buffer.memoryRequirements().size;

	uint32_t typeFilter = buffer.memoryRequirements().memoryTypeBits;
	auto memProperties = dev.physicalDeviceTraits().memoryProperties();
	uint32_t index;
	for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
		if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
			index = i;
		}
	}

	allocInfo.memoryTypeIndex = index;

	VkDeviceMemory mem;
	VkResult result = dev.vk().vkAllocateMemory(dev.handle(), &allocInfo, nullptr, &mem);
	if (result != VK_SUCCESS) {
		throw DevaExternalFailureException("Vulkan", "Could not allocated device memory");
	}

	return VulkanMemory(dev, mem, allocInfo.allocationSize, dev.physicalDeviceTraits().memoryProperties().memoryTypes[index], index);
}

VulkanMemory::VulkanMemory() noexcept = default;

VulkanMemory::VulkanMemory(const VulkanDevice &dev, VkDeviceMemory handle, VkDeviceSize size, const VkMemoryType &type, uint32_t typeIndex)
	: mHandle(dev.handle(), dev.vk().vkFreeMemory, handle),
	mSize(size),
	mType(type),
	mTypeIndex(typeIndex) {}

VulkanMemory::VulkanMemory(VulkanMemory &&memory) noexcept
	: mHandle(std::move(memory.mHandle)),
	mSize(memory.mSize),
	mType(memory.mType),
	mTypeIndex(memory.mTypeIndex) {}

VulkanMemory& VulkanMemory::operator=(VulkanMemory &&memory) noexcept {

	if (this == &memory) return *this;

	mHandle = std::move(memory.mHandle);
	mSize = memory.mSize;
	mType = memory.mType;
	mTypeIndex = memory.mTypeIndex;

	return *this;
}

void VulkanMemory::free() {
	mHandle.replace();
}