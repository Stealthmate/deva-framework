#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_CONTEXT_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_CONTEXT_HPP

#include "Config.hpp"

#include "VulkanInstance.hpp"

namespace DevaFramework
{
	class VulkanContext
	{
		struct SwapChainBuffer {
			VkImage image;
			VkImageView view;
		};

		VulkanInstance vk_instance;

		VkInstance instance;
		VkDevice device;
		VkPhysicalDevice physicalDevice;
		VkSurfaceKHR surface;
		VkFormat colorFormat;
		VkColorSpaceKHR colorSpace;
		VkSwapchainKHR swapChain;
		std::vector<VkImage> images;
		std::vector<SwapChainBuffer> buffers;
		size_t nodeIndex;
		PFN_vkGetPhysicalDeviceSurfaceSupportKHR fpGetPhysicalDeviceSurfaceSupportKHR;
		PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR fpGetPhysicalDeviceSurfaceCapabilitiesKHR;
		PFN_vkGetPhysicalDeviceSurfaceFormatsKHR fpGetPhysicalDeviceSurfaceFormatsKHR;
		PFN_vkGetPhysicalDeviceSurfacePresentModesKHR fpGetPhysicalDeviceSurfacePresentModesKHR;
		PFN_vkCreateSwapchainKHR fpCreateSwapchainKHR;
		PFN_vkDestroySwapchainKHR fpDestroySwapchainKHR;
		PFN_vkGetSwapchainImagesKHR fpGetSwapchainImagesKHR;
		PFN_vkAcquireNextImageKHR fpAcquireNextImageKHR;
		PFN_vkQueuePresentKHR fpQueuePresentKHR;

	public:
		VulkanContext & createContext(
		VulkanInstance & vkInstance
		
		
		);


	};
}


#endif DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_CONTEXT_HPP