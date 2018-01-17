#include "VulkanMemory.hpp"

using namespace DevaFramework;

uint32_t Vulkan::findMemoryTypeIndex(const VkPhysicalDeviceMemoryProperties &pdevMemProp, uint32_t memoryBits, VkMemoryPropertyFlags properties) {
	uint32_t index;
	for (uint32_t i = 0; i < pdevMemProp.memoryTypeCount; i++) {
		if ((memoryBits & (1 << i)) && (pdevMemProp.memoryTypes[i].propertyFlags & properties) == properties) {
			index = i;
		}
	}

	return index;
}

VulkanMemory Vulkan::allocateMemoryForBuffer(const VulkanDevice &dev, const VulkanBuffer &buffer, VkMemoryPropertyFlags properties) {
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

	allocInfo.memoryTypeIndex = findMemoryTypeIndex(dev.info().physicalDeviceTraits.memoryProperties(), buffer.info().memoryRequirements.memoryTypeBits, properties);

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

VulkanMemory Vulkan::allocateMemoryForImage(const VulkanDevice &device, const VulkanImage &image, VkMemoryPropertyFlags properties) {
	auto dev = device.handle();
	auto& vk = device.vk();

	VkMemoryRequirements memreq;
	vk.vkGetImageMemoryRequirements(dev, image.handle(), &memreq);

	VkResult res;
	VkMemoryAllocateInfo info;
	info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	info.pNext = nullptr;
	info.allocationSize = memreq.size;
	info.memoryTypeIndex = findMemoryTypeIndex(device.info().physicalDeviceTraits.memoryProperties(), memreq.memoryTypeBits, properties);

	VkDeviceMemory imageMemory;

	res = vk.vkAllocateMemory(dev, &info, nullptr, &imageMemory);
	if (res != VK_SUCCESS) {
		throw DevaException("Failed to allocate image memory!");
	}

	VulkanMemoryInfo memInfo;
	memInfo.size = info.allocationSize;
	memInfo.type = device.info().physicalDeviceTraits.memoryProperties().memoryTypes[info.memoryTypeIndex];
	memInfo.typeIndex = info.memoryTypeIndex;

	return VulkanMemory(imageMemory, memInfo);
}