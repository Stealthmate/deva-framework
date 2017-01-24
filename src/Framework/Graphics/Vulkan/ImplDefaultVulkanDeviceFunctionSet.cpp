#include "ImplDefaultVulkanDeviceFunctionSet.hpp"

using namespace DevaFramework;

void DevaFramework::internal::impldef_vkGetDeviceQueue(VkDevice device, uint32_t queueFamilyIndex, uint32_t queueIndex, VkQueue* pQueue)
{
	VULKAN_ERR.println("Called vkGetDeviceQueue with invalid driver PFN");
}

void DevaFramework::internal::impldef_vkDestroyDevice(VkDevice device, const VkAllocationCallbacks* pAllocator)
{
	VULKAN_ERR.println("Called vkDestroyDevice with invalid driver PFN");
}

VkResult DevaFramework::internal::impldef_vkDeviceWaitIdle(VkDevice device)
{
	VULKAN_ERR.println("Called vkDeviceWaitIdle with invalid driver PFN");
	return VK_SUCCESS;
}

VkResult DevaFramework::internal::impldef_vkGetSwapchainImagesKHR(VkDevice device, VkSwapchainKHR swapchain, uint32_t* pSwapchainImageCount, VkImage* pSwapchainImages)
{
	VULKAN_ERR.println("Called vkGetSwapchainImagesKHR with invalid driver PFN");
	return VK_SUCCESS;
}

VkResult DevaFramework::internal::impldef_vkCreateSwapchainKHR(VkDevice device, const VkSwapchainCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchain)
{
	VULKAN_ERR.println("Called vkCreateSwapchainKHR without proper driver PFN");
	return VK_SUCCESS;
}
VkResult DevaFramework::internal::impldef_vkAcquireNextImageKHR(VkDevice device, VkSwapchainKHR swapchain, uint64_t timeout, VkSemaphore semaphore, VkFence fence, uint32_t* pImageIndex)
{
	VULKAN_ERR.println("Called vkAcquireNextImageKHR without proper driver PFN");
	return VK_SUCCESS;
}
VkResult DevaFramework::internal::impldef_vkQueuePresentKHR(VkQueue queue, const VkPresentInfoKHR* pPresentInfo)
{
	VULKAN_ERR.println("Called vkQueuePresentKHR without proper driver PFN");
	return VK_SUCCESS;
}
void DevaFramework::internal::impldef_vkDestroySwapchainKHR(VkDevice device, VkSwapchainKHR swapchain, const VkAllocationCallbacks* pAllocator)
{
	VULKAN_ERR.println("Called vkDestroySwapchainKHR without proper driver PFN");
}

VkResult DevaFramework::internal::impldef_vkCreateImageView(VkDevice device, const VkImageViewCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkImageView* pView)
{
	VULKAN_ERR.println("Called vkCreateImageView without proper driver PFN");
	return VK_SUCCESS;
}