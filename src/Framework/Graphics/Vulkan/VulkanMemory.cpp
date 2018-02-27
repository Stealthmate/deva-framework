#include "VulkanMemory.hpp"

#include "VulkanDevice.hpp"
#include "VulkanBuffer.hpp"
#include "VulkanImage.hpp"

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

VulkanMemoryAlloc Vulkan::allocateMemoryForBuffer(const VulkanDevice &dev, const VulkanBuffer &buffer, VkMemoryPropertyFlags properties) {
	VkMemoryAllocateInfo allocInfo;
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.pNext = nullptr;
	allocInfo.allocationSize = buffer.memoryRequirements.size;

	uint32_t typeFilter = buffer.memoryRequirements.memoryTypeBits;
	auto memProperties = dev.physicalDevice.memoryProperties;
	uint32_t index;
	for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
		if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
			index = i;
		}
	}

	allocInfo.memoryTypeIndex = findMemoryTypeIndex(dev.physicalDevice.memoryProperties, buffer.memoryRequirements.memoryTypeBits, properties);

	VulkanMemoryAlloc memory;

	VkResult result = dev.vk.vkAllocateMemory(dev.handle, &allocInfo, nullptr, &memory.handle);
	if (result != VK_SUCCESS) {
		throw DevaExternalFailureException("Vulkan", "Could not allocated device memory");
	}

	memory.size = allocInfo.allocationSize;
	memory.typeIndex = allocInfo.memoryTypeIndex;
	memory.type = dev.physicalDevice.memoryProperties.memoryTypes[index];

	return memory;
}

VulkanMemoryAlloc Vulkan::allocateMemoryForImage(const VulkanDevice &device, const VulkanImage &image, VkMemoryPropertyFlags properties) {
	auto dev = device.handle;
	auto& vk = device.vk;

	VulkanMemoryAlloc memory;

	VkMemoryRequirements memreq;
	vk.vkGetImageMemoryRequirements(dev, image.handle, &memreq);

	VkResult res;
	VkMemoryAllocateInfo info;
	info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	info.pNext = nullptr;
	info.allocationSize = memreq.size;
	info.memoryTypeIndex = findMemoryTypeIndex(device.physicalDevice.memoryProperties, memreq.memoryTypeBits, properties);

	res = vk.vkAllocateMemory(dev, &info, nullptr, &memory.handle);
	if (res != VK_SUCCESS) {
		throw DevaException("Failed to allocate image memory!");
	}

	memory.size = info.allocationSize;
	memory.type = device.physicalDevice.memoryProperties.memoryTypes[info.memoryTypeIndex];
	memory.typeIndex = info.memoryTypeIndex;

	return memory;
}

void Vulkan::destroyObject(const VulkanDevice &dev, VulkanMemoryAlloc &mem) {
	dev.vk.vkFreeMemory(dev.handle, mem.handle, nullptr);
	mem.handle = VK_NULL_HANDLE;
}