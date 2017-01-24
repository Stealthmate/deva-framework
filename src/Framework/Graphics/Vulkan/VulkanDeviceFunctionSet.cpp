#include "VulkanDeviceFunctionSet.hpp"
#include "ImplDefaultVulkanDeviceFunctionSet.hpp"

using namespace DevaFramework;

#define LOAD(PFNNAME) \
VULKAN_LOG.println("Getting Device PFN_" #PFNNAME "..."); \
devf.PFNNAME = (PFN_##PFNNAME) vkinstance.getFunctionSet().vkGetDeviceProcAddr(vkdevice, #PFNNAME); \
if(devf.PFNNAME == NULL) \
{ \
	VULKAN_WARN.println("Device PFN_" #PFNNAME " not available (Extension not specified in VkDeviceCreateInfo?)"); \
	/*devf.PFNNAME = (PFN_##PFNNAME) internal::impldef_##PFNNAME; */\
}

VulkanDeviceFunctionSet VulkanDeviceFunctionSet::load(VkDevice vkdevice, const VulkanInstance &vkinstance)
{
	VulkanDeviceFunctionSet devf;
	LOAD(vkGetDeviceQueue);
	LOAD(vkDestroyDevice);
	LOAD(vkDeviceWaitIdle);
	LOAD(vkGetSwapchainImagesKHR);
	LOAD(vkAcquireNextImageKHR);
	LOAD(vkCreateSwapchainKHR);
	LOAD(vkQueuePresentKHR);
	LOAD(vkCreateImageView);
	LOAD(vkCreateShaderModule);
	LOAD(vkDestroyShaderModule);
	LOAD(vkCreatePipelineLayout);
	LOAD(vkCreateRenderPass);
	LOAD(vkDestroyRenderPass);
	LOAD(vkCreateGraphicsPipelines);
	LOAD(vkDestroyPipeline);
	LOAD(vkCreateFramebuffer);
	LOAD(vkDestroyCommandPool);
	LOAD(vkCreateCommandPool);
	LOAD(vkAllocateCommandBuffers);
	LOAD(vkBeginCommandBuffer);
	LOAD(vkCmdBeginRenderPass);
	LOAD(vkCmdBindPipeline);
	LOAD(vkCmdDraw);
	LOAD(vkCmdEndRenderPass);
	LOAD(vkEndCommandBuffer);
	LOAD(vkCreateSemaphore);
	LOAD(vkDestroySemaphore);
	LOAD(vkQueueSubmit);
	return devf;
}

VulkanDeviceFunctionSet::VulkanDeviceFunctionSet() = default;
VulkanDeviceFunctionSet::VulkanDeviceFunctionSet(const VulkanDeviceFunctionSet &fset) = default;
VulkanDeviceFunctionSet::VulkanDeviceFunctionSet(VulkanDeviceFunctionSet &&fset) = default;

VulkanDeviceFunctionSet& VulkanDeviceFunctionSet::operator=(const VulkanDeviceFunctionSet &fset) = default;
VulkanDeviceFunctionSet& VulkanDeviceFunctionSet::operator=(VulkanDeviceFunctionSet &&fset) = default;

VulkanDeviceFunctionSet::~VulkanDeviceFunctionSet() = default;