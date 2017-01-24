#ifndef DEVA_ENGINE_VULKAN_SWAPCHAIN_HPP
#define DEVA_ENGINE_VULKAN_SWAPCHAIN_HPP

#include "Config.hpp"

#include <DevaFramework/Graphics/Vulkan/VulkanDevice.hpp>
#include <DevaFramework/Graphics/Vulkan/VulkanDeviceFunctionSet.hpp>
#include <DevaFramework\Graphics\Vulkan\VulkanDeleter.hpp>

namespace DevaEngine {
	class VulkanSwapchain {

	public:

		DEVA_ENGINE_API static VulkanSwapchain createSwapchain(const DevaFramework::VulkanDevice &dev, const VkSwapchainCreateInfoKHR &createInfo);

		VkSwapchainKHR handle;
		std::vector<VkImage> images;
		std::vector<VkImageView> imageViews;
		VkExtent2D extent;
		VkFormat format;
		std::vector<VkFramebuffer> framebuffers;
	
		DEVA_ENGINE_API VulkanSwapchain();

	private:
		VulkanSwapchain(const DevaFramework::VulkanDevice &dev, const VkSwapchainKHR &swapchain, const VkSwapchainCreateInfoKHR &createInfo);

	};
}

#endif //DEVA_ENGINE_VULKAN_SWAPCHAIN_HPP