#include "VulkanSwapchain.hpp"
using namespace DevaFramework;
using namespace DevaEngine;

namespace {

}

VulkanSwapchain VulkanSwapchain::createSwapchain(const VulkanDevice &dev, const VkSwapchainCreateInfoKHR &createInfo)
{
	VkSwapchainKHR swapchain;
	auto result = dev.vk().vkCreateSwapchainKHR(dev.handle(), &createInfo, nullptr, &swapchain);
	if (result != VK_SUCCESS)
		throw DevaException("Could not create Swapchain");
	return VulkanSwapchain(dev, swapchain, createInfo);
}

VulkanSwapchain::VulkanSwapchain()
{
	this->handle = VK_NULL_HANDLE;
}

VulkanSwapchain::VulkanSwapchain(const VulkanDevice &dev, const VkSwapchainKHR &swapchain, const VkSwapchainCreateInfoKHR &createInfo)
{
	this->handle = swapchain;
	this->format = createInfo.imageFormat;
	this->extent = createInfo.imageExtent;
	auto vk = dev.vk();
	uint32_t imageCount = -1;
	vk.vkGetSwapchainImagesKHR(dev.handle(), this->handle, &imageCount, nullptr);
	this->images.resize(imageCount);
	vk.vkGetSwapchainImagesKHR(dev.handle(), this->handle, &imageCount, this->images.data());

	this->imageViews.resize(imageCount);
	for (int i = 0; i < this->images.size(); i++)
	{
		VkImageViewCreateInfo cinfo = {};
		cinfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		cinfo.image = this->images[i];
		cinfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		cinfo.format = this->format;
		cinfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		cinfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		cinfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		cinfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
		cinfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		cinfo.subresourceRange.baseMipLevel = 0;
		cinfo.subresourceRange.levelCount = 1;
		cinfo.subresourceRange.baseArrayLayer = 0;
		cinfo.subresourceRange.layerCount = 1;

		if (vk.vkCreateImageView(dev.handle(), &cinfo, nullptr, &this->imageViews[i]) != VK_SUCCESS) {
			throw DevaException("failed to create image views!");
		}
	}

	framebuffers.resize(imageViews.size());
}