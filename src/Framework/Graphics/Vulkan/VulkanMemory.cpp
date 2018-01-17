#include "VulkanMemory.hpp"

using namespace DevaFramework;

VulkanMemory Vulkan::allocateMemoryForBuffer(const VulkanBuffer &buffer, const VulkanDevice &dev, VkMemoryPropertyFlags properties) {
	VkMemoryAllocateInfo allocInfo;
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.pNext = nullptr;
	allocInfo.allocationSize = buffer.info().size;

	uint32_t typeFilter = buffer.info().memoryRequirements.memoryTypeBits;
	auto memProperties = dev.info().physicalDeviceTraits.memoryProperties();
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

	VulkanMemoryInfo info;
	info.size = allocInfo.allocationSize;
	info.typeIndex = allocInfo.memoryTypeIndex;
	info.type = dev.info().physicalDeviceTraits.memoryProperties().memoryTypes[index];

	return VulkanMemory(mem, info);
}