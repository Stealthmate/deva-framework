#include "VulkanMemoryManager.hpp"
#include <DevaFramework\Graphics\Vulkan\VulkanDevice.hpp>
#include <DevaFramework\Graphics\Vulkan\VulkanMemory.hpp>

using namespace DevaFramework;
using namespace DevaEngine;

uint32_t findMemoryTypeIndex(const VkPhysicalDeviceMemoryProperties &pdevMemProp, uint32_t memoryBits, VkMemoryPropertyFlags properties) {
	uint32_t index;
	for (uint32_t i = 0; i < pdevMemProp.memoryTypeCount; i++) {
		if ((memoryBits & (1 << i)) && (pdevMemProp.memoryTypes[i].propertyFlags & properties) == properties) {
			index = i;
		}
	}

	return index;
}

BasicVulkanMemoryManager::BasicVulkanMemoryManager(const VulkanDevice &dev) : device(dev) {}

std::shared_ptr<const VulkanMemoryRange> BasicVulkanMemoryManager::allocate(
	const VkMemoryRequirements &req,
	VkMemoryPropertyFlags properties) {

	auto dev = device.handle;
	auto &vk = device.vk;
	auto &pdev = device.physicalDevice;

	VkMemoryAllocateInfo allocInfo;
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.pNext = nullptr;
	allocInfo.allocationSize = req.size;

	uint32_t typeFilter = req.memoryTypeBits;
	auto memProperties = pdev.memoryProperties;
	uint32_t index;
	for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
		if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
			index = i;
		}
	}

	allocInfo.memoryTypeIndex = findMemoryTypeIndex(pdev.memoryProperties, req.memoryTypeBits, properties);

	VulkanMemoryAlloc memory;

	VkResult result = vk.vkAllocateMemory(dev, &allocInfo, nullptr, &memory.handle);
	if (result != VK_SUCCESS) {
		throw DevaExternalFailureException("Vulkan", "Could not allocated device memory");
	}

	memory.size = allocInfo.allocationSize;
	memory.typeIndex = allocInfo.memoryTypeIndex;
	memory.type = pdev.memoryProperties.memoryTypes[index];

	auto memrange = std::make_shared<VulkanMemoryRange>();
	memrange->memory = memory.handle;
	memrange->offset = 0;
	memrange->size = memory.size;
	return memrange;
}

void BasicVulkanMemoryManager::free(VulkanMemoryRange &range) {
	device.vk.vkFreeMemory(device.handle, range.memory, nullptr);
	range.memory = VK_NULL_HANDLE;
	range.offset = 0;
	range.size = 0;
}