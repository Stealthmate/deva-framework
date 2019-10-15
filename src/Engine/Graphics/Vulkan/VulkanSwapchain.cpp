#include "VulkanSwapchain.hpp"
using namespace DevaFramework;
using namespace DevaEngine;

namespace {

}

VulkanSwapchain DevaEngine::Vulkan::createSwapchain(const VulkanDevice &dev, const VkSwapchainCreateInfoKHR &createInfo)
{
	VulkanSwapchain swapchain;
	auto result = dev.vk.vkCreateSwapchainKHR(dev.handle, &createInfo, nullptr, &swapchain.handle);
	if (result != VK_SUCCESS)
		throw DevaException("Could not create Swapchain");

	swapchain.format = createInfo.imageFormat;
	swapchain.extent = createInfo.imageExtent;
	auto vk = dev.vk;
	uint32_t imageCount = -1;
	vk.vkGetSwapchainImagesKHR(dev.handle, swapchain.handle, &imageCount, nullptr);
	swapchain.images.resize(imageCount);
	vk.vkGetSwapchainImagesKHR(dev.handle, swapchain.handle, &imageCount, swapchain.images.data());

	swapchain.imageViews.resize(imageCount);
	for (int i = 0; i < swapchain.images.size(); i++)
	{
		VkImageViewCreateInfo cinfo = {};
		cinfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		cinfo.image = swapchain.images[i];
		cinfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		cinfo.format = swapchain.format;
		cinfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		cinfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		cinfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		cinfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
		cinfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		cinfo.subresourceRange.baseMipLevel = 0;
		cinfo.subresourceRange.levelCount = 1;
		cinfo.subresourceRange.baseArrayLayer = 0;
		cinfo.subresourceRange.layerCount = 1;

		if (vk.vkCreateImageView(dev.handle, &cinfo, nullptr, &swapchain.imageViews[i]) != VK_SUCCESS) {
			throw DevaException("failed to create image views!");
		}
	}

	return swapchain;
}