#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_IMPL_DEFAULT_VULKAN_DEVICE_FUNCTION_SET_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_IMPL_DEFAULT_VULKAN_DEVICE_FUNCTION_SET_HPP

#include "Config.hpp"

namespace DevaFramework
{
	namespace internal
	{
		void impldef_vkGetDeviceQueue(VkDevice device, uint32_t queueFamilyIndex, uint32_t queueIndex, VkQueue* pQueue);
		void impldef_vkDestroyDevice(VkDevice device, const VkAllocationCallbacks* pAllocator);
		VkResult impldef_vkGetSwapchainImagesKHR(VkDevice device, VkSwapchainKHR swapchain, uint32_t* pSwapchainImageCount, VkImage* pSwapchainImages);
		VkResult impldef_vkDeviceWaitIdle(VkDevice device);
		VkResult impldef_vkCreateSwapchainKHR(VkDevice device, const VkSwapchainCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchain);
		VkResult impldef_vkGetSwapchainImagesKHR(VkDevice device, VkSwapchainKHR swapchain, uint32_t* pSwapchainImageCount, VkImage* pSwapchainImages);
		VkResult impldef_vkAcquireNextImageKHR(VkDevice device, VkSwapchainKHR swapchain, uint64_t timeout, VkSemaphore semaphore, VkFence fence, uint32_t* pImageIndex);
		VkResult impldef_vkQueuePresentKHR(VkQueue queue, const VkPresentInfoKHR* pPresentInfo);
		VkResult impldef_vkCreateImageView(VkDevice device, const VkImageViewCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkImageView* pView);
		/*VkResult impldef_vkCreateShaderModule;
		VkResult impldef_vkDestroyShaderModule;
		VkResult impldef_vkCreatePipelineLayout;
		VkResult impldef_vkDestroyPipelineLayout;
		VkResult impldef_vkCreateRenderPass;
		VkResult impldef_vkDestroyRenderPass;
		VkResult impldef_vkCreateGraphicsPipelines;
		VkResult impldef_vkDestroyPipeline;
		VkResult impldef_vkCreateFramebuffer;
		VkResult impldef_vkDestroyCommandPool;
		VkResult impldef_vkCreateCommandPool;
		VkResult impldef_vkAllocateCommandBuffers;
		VkResult impldef_vkBeginCommandBuffer;
		VkResult impldef_vkCmdBeginRenderPass;
		VkResult impldef_vkCmdBindPipeline;
		VkResult impldef_vkCmdDraw;
		VkResult impldef_vkCmdEndRenderPass;
		VkResult impldef_vkEndCommandBuffer;
		VkResult impldef_vkCreateSemaphore;
		VkResult impldef_vkDestroySemaphore;*/
		
		
		
		void  impldef_vkDestroySwapchainKHR(VkDevice device, VkSwapchainKHR swapchain, const VkAllocationCallbacks* pAllocator);

	}
}

#endif //DEVA_FRAMEWORK_GRAPHICS_VULKAN_IMPL_DEFAULT_VULKAN_DEVICE_FUNCTION_SET_HPP