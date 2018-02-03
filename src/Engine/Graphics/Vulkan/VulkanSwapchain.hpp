#ifndef DEVA_ENGINE_VULKAN_SWAPCHAIN_HPP
#define DEVA_ENGINE_VULKAN_SWAPCHAIN_HPP

#include "Config.hpp"

#include <DevaFramework\Graphics\Vulkan\VulkanDevice.hpp>
#include <DevaFramework\Graphics\Vulkan\VulkanDeviceFunctionSet.hpp>
#include <DevaFramework\Graphics\Vulkan\VulkanHandle.hpp>

namespace DevaEngine {
	struct VulkanSwapchain {
		VkSwapchainKHR handle;
		std::vector<VkImage> images;
		std::vector<VkImageView> imageViews;
		VkExtent2D extent;
		VkFormat format;
	};

	namespace Vulkan {
		DEVA_ENGINE_API VulkanSwapchain createSwapchain(
			const DevaFramework::VulkanDevice &dev,
			const VkSwapchainCreateInfoKHR &info);
	}
}

#endif //DEVA_ENGINE_VULKAN_SWAPCHAIN_HPP