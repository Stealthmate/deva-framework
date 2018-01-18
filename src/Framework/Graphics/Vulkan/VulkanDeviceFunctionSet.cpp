#include "VulkanDeviceFunctionSet.hpp"
#include "ImplDefaultVulkanDeviceFunctionSet.hpp"

using namespace DevaFramework;

#define LOAD(PFNNAME) \
LOG_VULKAN.v("Getting Device PFN_" #PFNNAME "..."); \
devf.PFNNAME = (PFN_##PFNNAME) vkinstance.vk.vkGetDeviceProcAddr(vkdevice, #PFNNAME); \
if(devf.PFNNAME == NULL) \
{ \
	LOG_VULKAN.v("Device PFN_" #PFNNAME " not available. Assigning default implementation (throw exception)"); \
	devf.PFNNAME = (PFN_##PFNNAME) internal::impldef_##PFNNAME;\
}

VulkanDeviceFunctionSet VulkanDeviceFunctionSet::load(VkDevice vkdevice, const VulkanInstance &vkinstance)
{
	VulkanDeviceFunctionSet devf;

	LOAD(vkVoidFunction);
	LOAD(vkCreateInstance);
	LOAD(vkGetDeviceProcAddr);
	LOAD(vkDestroyDevice);
	LOAD(vkEnumerateInstanceExtensionProperties);
	LOAD(vkEnumerateInstanceLayerProperties);
	LOAD(vkGetDeviceQueue);
	LOAD(vkQueueSubmit);
	LOAD(vkQueueWaitIdle);
	LOAD(vkDeviceWaitIdle);
	LOAD(vkAllocateMemory);
	LOAD(vkFreeMemory);
	LOAD(vkMapMemory);
	LOAD(vkUnmapMemory);
	LOAD(vkFlushMappedMemoryRanges);
	LOAD(vkInvalidateMappedMemoryRanges);
	LOAD(vkGetDeviceMemoryCommitment);
	LOAD(vkBindBufferMemory);
	LOAD(vkBindImageMemory);
	LOAD(vkGetBufferMemoryRequirements);
	LOAD(vkGetImageMemoryRequirements);
	LOAD(vkGetImageSparseMemoryRequirements);
	LOAD(vkQueueBindSparse);
	LOAD(vkCreateFence);
	LOAD(vkDestroyFence);
	LOAD(vkResetFences);
	LOAD(vkGetFenceStatus);
	LOAD(vkWaitForFences);
	LOAD(vkCreateSemaphore);
	LOAD(vkDestroySemaphore);
	LOAD(vkCreateEvent);
	LOAD(vkDestroyEvent);
	LOAD(vkGetEventStatus);
	LOAD(vkSetEvent);
	LOAD(vkResetEvent);
	LOAD(vkCreateQueryPool);
	LOAD(vkDestroyQueryPool);
	LOAD(vkGetQueryPoolResults);
	LOAD(vkCreateBuffer);
	LOAD(vkDestroyBuffer);
	LOAD(vkCreateBufferView);
	LOAD(vkDestroyBufferView);
	LOAD(vkCreateImage);
	LOAD(vkDestroyImage);
	LOAD(vkGetImageSubresourceLayout);
	LOAD(vkCreateImageView);
	LOAD(vkDestroyImageView);
	LOAD(vkCreateShaderModule);
	LOAD(vkDestroyShaderModule);
	LOAD(vkCreatePipelineCache);
	LOAD(vkDestroyPipelineCache);
	LOAD(vkGetPipelineCacheData);
	LOAD(vkMergePipelineCaches);
	LOAD(vkCreateGraphicsPipelines);
	LOAD(vkCreateComputePipelines);
	LOAD(vkDestroyPipeline);
	LOAD(vkCreatePipelineLayout);
	LOAD(vkDestroyPipelineLayout);
	LOAD(vkCreateSampler);
	LOAD(vkDestroySampler);
	LOAD(vkCreateDescriptorSetLayout);
	LOAD(vkDestroyDescriptorSetLayout);
	LOAD(vkCreateDescriptorPool);
	LOAD(vkDestroyDescriptorPool);
	LOAD(vkResetDescriptorPool);
	LOAD(vkAllocateDescriptorSets);
	LOAD(vkFreeDescriptorSets);
	LOAD(vkUpdateDescriptorSets);
	LOAD(vkCreateFramebuffer);
	LOAD(vkDestroyFramebuffer);
	LOAD(vkCreateRenderPass);
	LOAD(vkDestroyRenderPass);
	LOAD(vkGetRenderAreaGranularity);
	LOAD(vkCreateCommandPool);
	LOAD(vkDestroyCommandPool);
	LOAD(vkResetCommandPool);
	LOAD(vkAllocateCommandBuffers);
	LOAD(vkFreeCommandBuffers);
	LOAD(vkBeginCommandBuffer);
	LOAD(vkEndCommandBuffer);
	LOAD(vkResetCommandBuffer);
	LOAD(vkCmdBindPipeline);
	LOAD(vkCmdSetViewport);
	LOAD(vkCmdSetScissor);
	LOAD(vkCmdSetLineWidth);
	LOAD(vkCmdSetDepthBias);
	LOAD(vkCmdSetBlendConstants);
	LOAD(vkCmdSetDepthBounds);
	LOAD(vkCmdSetStencilCompareMask);
	LOAD(vkCmdSetStencilWriteMask);
	LOAD(vkCmdSetStencilReference);
	LOAD(vkCmdBindDescriptorSets);
	LOAD(vkCmdBindIndexBuffer);
	LOAD(vkCmdBindVertexBuffers);
	LOAD(vkCmdDraw);
	LOAD(vkCmdDrawIndexed);
	LOAD(vkCmdDrawIndirect);
	LOAD(vkCmdDrawIndexedIndirect);
	LOAD(vkCmdDispatch);
	LOAD(vkCmdDispatchIndirect);
	LOAD(vkCmdCopyBuffer);
	LOAD(vkCmdCopyImage);
	LOAD(vkCmdBlitImage);
	LOAD(vkCmdCopyBufferToImage);
	LOAD(vkCmdCopyImageToBuffer);
	LOAD(vkCmdUpdateBuffer);
	LOAD(vkCmdFillBuffer);
	LOAD(vkCmdClearColorImage);
	LOAD(vkCmdClearDepthStencilImage);
	LOAD(vkCmdClearAttachments);
	LOAD(vkCmdResolveImage);
	LOAD(vkCmdSetEvent);
	LOAD(vkCmdResetEvent);
	LOAD(vkCmdWaitEvents);
	LOAD(vkCmdPipelineBarrier);
	LOAD(vkCmdBeginQuery);
	LOAD(vkCmdEndQuery);
	LOAD(vkCmdResetQueryPool);
	LOAD(vkCmdWriteTimestamp);
	LOAD(vkCmdCopyQueryPoolResults);
	LOAD(vkCmdPushConstants);
	LOAD(vkCmdBeginRenderPass);
	LOAD(vkCmdNextSubpass);
	LOAD(vkCmdEndRenderPass);
	LOAD(vkCmdExecuteCommands);
	LOAD(vkCreateSwapchainKHR);
	LOAD(vkDestroySwapchainKHR);
	LOAD(vkGetSwapchainImagesKHR);
	LOAD(vkAcquireNextImageKHR);
	LOAD(vkQueuePresentKHR);
	LOAD(vkCreateSharedSwapchainsKHR);
	LOAD(vkDebugMarkerSetObjectTagEXT);
	LOAD(vkDebugMarkerSetObjectNameEXT);
	LOAD(vkCmdDebugMarkerBeginEXT);
	LOAD(vkCmdDebugMarkerEndEXT);
	LOAD(vkCmdDebugMarkerInsertEXT);
	LOAD(vkCmdDrawIndirectCountAMD);
	LOAD(vkCmdDrawIndexedIndirectCountAMD);
#ifdef VK_USE_PLATFORM_WIN32_KHR
	LOAD(vkGetMemoryWin32HandleNV);
#endif
	LOAD(vkCmdProcessCommandsNVX);
	LOAD(vkCmdReserveSpaceForCommandsNVX);
	LOAD(vkCreateIndirectCommandsLayoutNVX);
	LOAD(vkDestroyIndirectCommandsLayoutNVX);
	LOAD(vkCreateObjectTableNVX);
	LOAD(vkDestroyObjectTableNVX);
	LOAD(vkRegisterObjectsNVX);
	LOAD(vkUnregisterObjectsNVX);

	return devf;
}

VulkanDeviceFunctionSet::VulkanDeviceFunctionSet() = default;
VulkanDeviceFunctionSet::VulkanDeviceFunctionSet(const VulkanDeviceFunctionSet &fset) = default;
VulkanDeviceFunctionSet::VulkanDeviceFunctionSet(VulkanDeviceFunctionSet &&fset) = default;

VulkanDeviceFunctionSet& VulkanDeviceFunctionSet::operator=(const VulkanDeviceFunctionSet &fset) = default;
VulkanDeviceFunctionSet& VulkanDeviceFunctionSet::operator=(VulkanDeviceFunctionSet &&fset) = default;

VulkanDeviceFunctionSet::~VulkanDeviceFunctionSet() = default;