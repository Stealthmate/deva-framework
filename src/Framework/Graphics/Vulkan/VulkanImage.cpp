#include "VulkanImage.hpp"

#include "VulkanDevice.hpp"

using namespace DevaFramework;

void Vulkan::destroyObject(const VulkanDevice &dev, VulkanImage &img) {
	dev.vk.vkDestroyImage(dev.handle, img.handle, nullptr);
	img.handle = VK_NULL_HANDLE;
}