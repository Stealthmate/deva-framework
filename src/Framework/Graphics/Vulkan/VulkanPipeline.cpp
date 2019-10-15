#include "VulkanPipeline.hpp"

#include "VulkanDevice.hpp"

using namespace DevaFramework;

void Vulkan::destroyObject(const VulkanDevice &device, VulkanGraphicsPipeline &obj) {
	device.vk.vkDestroyPipeline(device.handle, obj.handle, nullptr);
	obj.handle = VK_NULL_HANDLE;
}