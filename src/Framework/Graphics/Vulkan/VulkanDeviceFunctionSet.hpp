#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_DEVICE_FUNCTION_SET_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_DEVICE_FUNCTION_SET_HPP

#include "Config.hpp"

#include "VulkanInstance.hpp"

namespace DevaFramework
{
	struct VulkanDeviceFunctionSet
	{
		DEVA_FRAMEWORK_API static VulkanDeviceFunctionSet load(VkDevice vkDevice, const VulkanInstance &vkInstance);

		PFN_vkGetDeviceQueue                                           vkGetDeviceQueue;
		PFN_vkDestroyDevice                                            vkDestroyDevice;
		PFN_vkDeviceWaitIdle                                           vkDeviceWaitIdle;
		PFN_vkGetSwapchainImagesKHR                                    vkGetSwapchainImagesKHR;
		PFN_vkCreateSwapchainKHR                                       vkCreateSwapchainKHR;
		PFN_vkAcquireNextImageKHR							           vkAcquireNextImageKHR;
		PFN_vkQueuePresentKHR                                          vkQueuePresentKHR;
		PFN_vkCreateImageView                                          vkCreateImageView;
		PFN_vkCreateShaderModule                                       vkCreateShaderModule;
		PFN_vkDestroyShaderModule                                      vkDestroyShaderModule;
		PFN_vkCreatePipelineLayout 	                                   vkCreatePipelineLayout;
		PFN_vkDestroyPipelineLayout	                                   vkDestroyPipelineLayout;
		PFN_vkCreateRenderPass	                                       vkCreateRenderPass;
		PFN_vkDestroyRenderPass	                                       vkDestroyRenderPass;
		PFN_vkCreateGraphicsPipelines		                           vkCreateGraphicsPipelines;
		PFN_vkDestroyPipeline				                           vkDestroyPipeline;
		PFN_vkCreateFramebuffer                                        vkCreateFramebuffer;
		PFN_vkDestroyCommandPool                                       vkDestroyCommandPool;
		PFN_vkCreateCommandPool	                                       vkCreateCommandPool;
		PFN_vkAllocateCommandBuffers	                               vkAllocateCommandBuffers;
		PFN_vkBeginCommandBuffer		                               vkBeginCommandBuffer;
		PFN_vkCmdBeginRenderPass	                                   vkCmdBeginRenderPass;
		PFN_vkCmdBindPipeline	                                       vkCmdBindPipeline;
		PFN_vkCmdDraw		                                           vkCmdDraw;
		PFN_vkCmdEndRenderPass	                                       vkCmdEndRenderPass;
		PFN_vkEndCommandBuffer			                               vkEndCommandBuffer;
		PFN_vkCreateSemaphore										   vkCreateSemaphore;
		PFN_vkDestroySemaphore										   vkDestroySemaphore;
		PFN_vkQueueSubmit                                              vkQueueSubmit;


		DEVA_FRAMEWORK_API VulkanDeviceFunctionSet();
		DEVA_FRAMEWORK_API VulkanDeviceFunctionSet(const VulkanDeviceFunctionSet &fset);
		DEVA_FRAMEWORK_API VulkanDeviceFunctionSet(VulkanDeviceFunctionSet &&fset);

		DEVA_FRAMEWORK_API VulkanDeviceFunctionSet& operator=(const VulkanDeviceFunctionSet &fset);
		DEVA_FRAMEWORK_API VulkanDeviceFunctionSet& operator=(VulkanDeviceFunctionSet &&fset);

		DEVA_FRAMEWORK_API ~VulkanDeviceFunctionSet();
	};

}

#endif //DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_DEVICE_FUNCTION_SET_HPP