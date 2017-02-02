#include "ImplDefaultVulkanDeviceFunctionSet.hpp"

using namespace DevaFramework;
void DevaFramework::internal::impldef_vkVoidFunction(void)
{
	VULKAN_ERR.println("Called vkVoidFunction without proper driver PFN");
	return;
}
VkResult DevaFramework::internal::impldef_vkCreateInstance(const VkInstanceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkInstance* pInstance)
{
	VULKAN_ERR.println("Called vkCreateInstance without proper driver PFN");
	return VK_SUCCESS;
}
PFN_vkVoidFunction DevaFramework::internal::impldef_vkGetDeviceProcAddr(VkDevice device, const char* pName)
{
	VULKAN_ERR.println("Called vkGetDeviceProcAddr without proper driver PFN");
	return nullptr;
}
void DevaFramework::internal::impldef_vkDestroyDevice(VkDevice device, const VkAllocationCallbacks* pAllocator)
{
	VULKAN_ERR.println("Called vkDestroyDevice without proper driver PFN");
	return;
}
VkResult DevaFramework::internal::impldef_vkEnumerateInstanceExtensionProperties(const char* pLayerName, uint32_t* pPropertyCount, VkExtensionProperties* pProperties)
{
	VULKAN_ERR.println("Called vkEnumerateInstanceExtensionProperties without proper driver PFN");
	return VK_SUCCESS;
}
VkResult DevaFramework::internal::impldef_vkEnumerateInstanceLayerProperties(uint32_t* pPropertyCount, VkLayerProperties* pProperties)
{
	VULKAN_ERR.println("Called vkEnumerateInstanceLayerProperties without proper driver PFN");
	return VK_SUCCESS;
}
void DevaFramework::internal::impldef_vkGetDeviceQueue(VkDevice device, uint32_t queueFamilyIndex, uint32_t queueIndex, VkQueue* pQueue)
{
	VULKAN_ERR.println("Called vkGetDeviceQueue without proper driver PFN");
	return;
}
VkResult DevaFramework::internal::impldef_vkQueueSubmit(VkQueue queue, uint32_t submitCount, const VkSubmitInfo* pSubmits, VkFence fence)
{
	VULKAN_ERR.println("Called vkQueueSubmit without proper driver PFN");
	return VK_SUCCESS;
}
VkResult DevaFramework::internal::impldef_vkQueueWaitIdle(VkQueue queue)
{
	VULKAN_ERR.println("Called vkQueueWaitIdle without proper driver PFN");
	return VK_SUCCESS;
}
VkResult DevaFramework::internal::impldef_vkDeviceWaitIdle(VkDevice device)
{
	VULKAN_ERR.println("Called vkDeviceWaitIdle without proper driver PFN");
	return VK_SUCCESS;
}
VkResult DevaFramework::internal::impldef_vkAllocateMemory(VkDevice device, const VkMemoryAllocateInfo* pAllocateInfo, const VkAllocationCallbacks* pAllocator, VkDeviceMemory* pMemory)
{
	VULKAN_ERR.println("Called vkAllocateMemory without proper driver PFN");
	return VK_SUCCESS;
}
void DevaFramework::internal::impldef_vkFreeMemory(VkDevice device, VkDeviceMemory memory, const VkAllocationCallbacks* pAllocator)
{
	VULKAN_ERR.println("Called vkFreeMemory without proper driver PFN");
	return;
}
VkResult DevaFramework::internal::impldef_vkMapMemory(VkDevice device, VkDeviceMemory memory, VkDeviceSize offset, VkDeviceSize size, VkMemoryMapFlags flags, void** ppData)
{
	VULKAN_ERR.println("Called vkMapMemory without proper driver PFN");
	return VK_SUCCESS;
}
void DevaFramework::internal::impldef_vkUnmapMemory(VkDevice device, VkDeviceMemory memory)
{
	VULKAN_ERR.println("Called vkUnmapMemory without proper driver PFN");
	return;
}
VkResult DevaFramework::internal::impldef_vkFlushMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, const VkMappedMemoryRange* pMemoryRanges)
{
	VULKAN_ERR.println("Called vkFlushMappedMemoryRanges without proper driver PFN");
	return VK_SUCCESS;
}
VkResult DevaFramework::internal::impldef_vkInvalidateMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, const VkMappedMemoryRange* pMemoryRanges)
{
	VULKAN_ERR.println("Called vkInvalidateMappedMemoryRanges without proper driver PFN");
	return VK_SUCCESS;
}
void DevaFramework::internal::impldef_vkGetDeviceMemoryCommitment(VkDevice device, VkDeviceMemory memory, VkDeviceSize* pCommittedMemoryInBytes)
{
	VULKAN_ERR.println("Called vkGetDeviceMemoryCommitment without proper driver PFN");
	return;
}
VkResult DevaFramework::internal::impldef_vkBindBufferMemory(VkDevice device, VkBuffer buffer, VkDeviceMemory memory, VkDeviceSize memoryOffset)
{
	VULKAN_ERR.println("Called vkBindBufferMemory without proper driver PFN");
	return VK_SUCCESS;
}
VkResult DevaFramework::internal::impldef_vkBindImageMemory(VkDevice device, VkImage image, VkDeviceMemory memory, VkDeviceSize memoryOffset)
{
	VULKAN_ERR.println("Called vkBindImageMemory without proper driver PFN");
	return VK_SUCCESS;
}
void DevaFramework::internal::impldef_vkGetBufferMemoryRequirements(VkDevice device, VkBuffer buffer, VkMemoryRequirements* pMemoryRequirements)
{
	VULKAN_ERR.println("Called vkGetBufferMemoryRequirements without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkGetImageMemoryRequirements(VkDevice device, VkImage image, VkMemoryRequirements* pMemoryRequirements)
{
	VULKAN_ERR.println("Called vkGetImageMemoryRequirements without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkGetImageSparseMemoryRequirements(VkDevice device, VkImage image, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements* pSparseMemoryRequirements)
{
	VULKAN_ERR.println("Called vkGetImageSparseMemoryRequirements without proper driver PFN");
	return;
}
VkResult DevaFramework::internal::impldef_vkQueueBindSparse(VkQueue queue, uint32_t bindInfoCount, const VkBindSparseInfo* pBindInfo, VkFence fence)
{
	VULKAN_ERR.println("Called vkQueueBindSparse without proper driver PFN");
	return VK_SUCCESS;
}
VkResult DevaFramework::internal::impldef_vkCreateFence(VkDevice device, const VkFenceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkFence* pFence)
{
	VULKAN_ERR.println("Called vkCreateFence without proper driver PFN");
	return VK_SUCCESS;
}
void DevaFramework::internal::impldef_vkDestroyFence(VkDevice device, VkFence fence, const VkAllocationCallbacks* pAllocator)
{
	VULKAN_ERR.println("Called vkDestroyFence without proper driver PFN");
	return;
}
VkResult DevaFramework::internal::impldef_vkResetFences(VkDevice device, uint32_t fenceCount, const VkFence* pFences)
{
	VULKAN_ERR.println("Called vkResetFences without proper driver PFN");
	return VK_SUCCESS;
}
VkResult DevaFramework::internal::impldef_vkGetFenceStatus(VkDevice device, VkFence fence)
{
	VULKAN_ERR.println("Called vkGetFenceStatus without proper driver PFN");
	return VK_SUCCESS;
}
VkResult DevaFramework::internal::impldef_vkWaitForFences(VkDevice device, uint32_t fenceCount, const VkFence* pFences, VkBool32 waitAll, uint64_t timeout)
{
	VULKAN_ERR.println("Called vkWaitForFences without proper driver PFN");
	return VK_SUCCESS;
}
VkResult DevaFramework::internal::impldef_vkCreateSemaphore(VkDevice device, const VkSemaphoreCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSemaphore* pSemaphore)
{
	VULKAN_ERR.println("Called vkCreateSemaphore without proper driver PFN");
	return VK_SUCCESS;
}
void DevaFramework::internal::impldef_vkDestroySemaphore(VkDevice device, VkSemaphore semaphore, const VkAllocationCallbacks* pAllocator)
{
	VULKAN_ERR.println("Called vkDestroySemaphore without proper driver PFN");
	return;
}
VkResult DevaFramework::internal::impldef_vkCreateEvent(VkDevice device, const VkEventCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkEvent* pEvent)
{
	VULKAN_ERR.println("Called vkCreateEvent without proper driver PFN");
	return VK_SUCCESS;
}
void DevaFramework::internal::impldef_vkDestroyEvent(VkDevice device, VkEvent event, const VkAllocationCallbacks* pAllocator)
{
	VULKAN_ERR.println("Called vkDestroyEvent without proper driver PFN");
	return;
}
VkResult DevaFramework::internal::impldef_vkGetEventStatus(VkDevice device, VkEvent event)
{
	VULKAN_ERR.println("Called vkGetEventStatus without proper driver PFN");
	return VK_SUCCESS;
}
VkResult DevaFramework::internal::impldef_vkSetEvent(VkDevice device, VkEvent event)
{
	VULKAN_ERR.println("Called vkSetEvent without proper driver PFN");
	return VK_SUCCESS;
}
VkResult DevaFramework::internal::impldef_vkResetEvent(VkDevice device, VkEvent event)
{
	VULKAN_ERR.println("Called vkResetEvent without proper driver PFN");
	return VK_SUCCESS;
}
VkResult DevaFramework::internal::impldef_vkCreateQueryPool(VkDevice device, const VkQueryPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkQueryPool* pQueryPool)
{
	VULKAN_ERR.println("Called vkCreateQueryPool without proper driver PFN");
	return VK_SUCCESS;
}
void DevaFramework::internal::impldef_vkDestroyQueryPool(VkDevice device, VkQueryPool queryPool, const VkAllocationCallbacks* pAllocator)
{
	VULKAN_ERR.println("Called vkDestroyQueryPool without proper driver PFN");
	return;
}
VkResult DevaFramework::internal::impldef_vkGetQueryPoolResults(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, size_t dataSize, void* pData, VkDeviceSize stride, VkQueryResultFlags flags)
{
	VULKAN_ERR.println("Called vkGetQueryPoolResults without proper driver PFN");
	return VK_SUCCESS;
}
VkResult DevaFramework::internal::impldef_vkCreateBuffer(VkDevice device, const VkBufferCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBuffer* pBuffer)
{
	VULKAN_ERR.println("Called vkCreateBuffer without proper driver PFN");
	return VK_SUCCESS;
}
void DevaFramework::internal::impldef_vkDestroyBuffer(VkDevice device, VkBuffer buffer, const VkAllocationCallbacks* pAllocator)
{
	VULKAN_ERR.println("Called vkDestroyBuffer without proper driver PFN");
	return;
}
VkResult DevaFramework::internal::impldef_vkCreateBufferView(VkDevice device, const VkBufferViewCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBufferView* pView)
{
	VULKAN_ERR.println("Called vkCreateBufferView without proper driver PFN");
	return VK_SUCCESS;
}
void DevaFramework::internal::impldef_vkDestroyBufferView(VkDevice device, VkBufferView bufferView, const VkAllocationCallbacks* pAllocator)
{
	VULKAN_ERR.println("Called vkDestroyBufferView without proper driver PFN");
	return;
}
VkResult DevaFramework::internal::impldef_vkCreateImage(VkDevice device, const VkImageCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkImage* pImage)
{
	VULKAN_ERR.println("Called vkCreateImage without proper driver PFN");
	return VK_SUCCESS;
}
void DevaFramework::internal::impldef_vkDestroyImage(VkDevice device, VkImage image, const VkAllocationCallbacks* pAllocator)
{
	VULKAN_ERR.println("Called vkDestroyImage without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkGetImageSubresourceLayout(VkDevice device, VkImage image, const VkImageSubresource* pSubresource, VkSubresourceLayout* pLayout)
{
	VULKAN_ERR.println("Called vkGetImageSubresourceLayout without proper driver PFN");
	return;
}
VkResult DevaFramework::internal::impldef_vkCreateImageView(VkDevice device, const VkImageViewCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkImageView* pView)
{
	VULKAN_ERR.println("Called vkCreateImageView without proper driver PFN");
	return VK_SUCCESS;
}
void DevaFramework::internal::impldef_vkDestroyImageView(VkDevice device, VkImageView imageView, const VkAllocationCallbacks* pAllocator)
{
	VULKAN_ERR.println("Called vkDestroyImageView without proper driver PFN");
	return;
}
VkResult DevaFramework::internal::impldef_vkCreateShaderModule(VkDevice device, const VkShaderModuleCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkShaderModule* pShaderModule)
{
	VULKAN_ERR.println("Called vkCreateShaderModule without proper driver PFN");
	return VK_SUCCESS;
}
void DevaFramework::internal::impldef_vkDestroyShaderModule(VkDevice device, VkShaderModule shaderModule, const VkAllocationCallbacks* pAllocator)
{
	VULKAN_ERR.println("Called vkDestroyShaderModule without proper driver PFN");
	return;
}
VkResult DevaFramework::internal::impldef_vkCreatePipelineCache(VkDevice device, const VkPipelineCacheCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineCache* pPipelineCache)
{
	VULKAN_ERR.println("Called vkCreatePipelineCache without proper driver PFN");
	return VK_SUCCESS;
}
void DevaFramework::internal::impldef_vkDestroyPipelineCache(VkDevice device, VkPipelineCache pipelineCache, const VkAllocationCallbacks* pAllocator)
{
	VULKAN_ERR.println("Called vkDestroyPipelineCache without proper driver PFN");
	return;
}
VkResult DevaFramework::internal::impldef_vkGetPipelineCacheData(VkDevice device, VkPipelineCache pipelineCache, size_t* pDataSize, void* pData)
{
	VULKAN_ERR.println("Called vkGetPipelineCacheData without proper driver PFN");
	return VK_SUCCESS;
}
VkResult DevaFramework::internal::impldef_vkMergePipelineCaches(VkDevice device, VkPipelineCache dstCache, uint32_t srcCacheCount, const VkPipelineCache* pSrcCaches)
{
	VULKAN_ERR.println("Called vkMergePipelineCaches without proper driver PFN");
	return VK_SUCCESS;
}
VkResult DevaFramework::internal::impldef_vkCreateGraphicsPipelines(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkGraphicsPipelineCreateInfo* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines)
{
	VULKAN_ERR.println("Called vkCreateGraphicsPipelines without proper driver PFN");
	return VK_SUCCESS;
}
VkResult DevaFramework::internal::impldef_vkCreateComputePipelines(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkComputePipelineCreateInfo* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines)
{
	VULKAN_ERR.println("Called vkCreateComputePipelines without proper driver PFN");
	return VK_SUCCESS;
}
void DevaFramework::internal::impldef_vkDestroyPipeline(VkDevice device, VkPipeline pipeline, const VkAllocationCallbacks* pAllocator)
{
	VULKAN_ERR.println("Called vkDestroyPipeline without proper driver PFN");
	return;
}
VkResult DevaFramework::internal::impldef_vkCreatePipelineLayout(VkDevice device, const VkPipelineLayoutCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineLayout* pPipelineLayout)
{
	VULKAN_ERR.println("Called vkCreatePipelineLayout without proper driver PFN");
	return VK_SUCCESS;
}
void DevaFramework::internal::impldef_vkDestroyPipelineLayout(VkDevice device, VkPipelineLayout pipelineLayout, const VkAllocationCallbacks* pAllocator)
{
	VULKAN_ERR.println("Called vkDestroyPipelineLayout without proper driver PFN");
	return;
}
VkResult DevaFramework::internal::impldef_vkCreateSampler(VkDevice device, const VkSamplerCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSampler* pSampler)
{
	VULKAN_ERR.println("Called vkCreateSampler without proper driver PFN");
	return VK_SUCCESS;
}
void DevaFramework::internal::impldef_vkDestroySampler(VkDevice device, VkSampler sampler, const VkAllocationCallbacks* pAllocator)
{
	VULKAN_ERR.println("Called vkDestroySampler without proper driver PFN");
	return;
}
VkResult DevaFramework::internal::impldef_vkCreateDescriptorSetLayout(VkDevice device, const VkDescriptorSetLayoutCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorSetLayout* pSetLayout)
{
	VULKAN_ERR.println("Called vkCreateDescriptorSetLayout without proper driver PFN");
	return VK_SUCCESS;
}
void DevaFramework::internal::impldef_vkDestroyDescriptorSetLayout(VkDevice device, VkDescriptorSetLayout descriptorSetLayout, const VkAllocationCallbacks* pAllocator)
{
	VULKAN_ERR.println("Called vkDestroyDescriptorSetLayout without proper driver PFN");
	return;
}
VkResult DevaFramework::internal::impldef_vkCreateDescriptorPool(VkDevice device, const VkDescriptorPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorPool* pDescriptorPool)
{
	VULKAN_ERR.println("Called vkCreateDescriptorPool without proper driver PFN");
	return VK_SUCCESS;
}
void DevaFramework::internal::impldef_vkDestroyDescriptorPool(VkDevice device, VkDescriptorPool descriptorPool, const VkAllocationCallbacks* pAllocator)
{
	VULKAN_ERR.println("Called vkDestroyDescriptorPool without proper driver PFN");
	return;
}
VkResult DevaFramework::internal::impldef_vkResetDescriptorPool(VkDevice device, VkDescriptorPool descriptorPool, VkDescriptorPoolResetFlags flags)
{
	VULKAN_ERR.println("Called vkResetDescriptorPool without proper driver PFN");
	return VK_SUCCESS;
}
VkResult DevaFramework::internal::impldef_vkAllocateDescriptorSets(VkDevice device, const VkDescriptorSetAllocateInfo* pAllocateInfo, VkDescriptorSet* pDescriptorSets)
{
	VULKAN_ERR.println("Called vkAllocateDescriptorSets without proper driver PFN");
	return VK_SUCCESS;
}
VkResult DevaFramework::internal::impldef_vkFreeDescriptorSets(VkDevice device, VkDescriptorPool descriptorPool, uint32_t descriptorSetCount, const VkDescriptorSet* pDescriptorSets)
{
	VULKAN_ERR.println("Called vkFreeDescriptorSets without proper driver PFN");
	return VK_SUCCESS;
}
void DevaFramework::internal::impldef_vkUpdateDescriptorSets(VkDevice device, uint32_t descriptorWriteCount, const VkWriteDescriptorSet* pDescriptorWrites, uint32_t descriptorCopyCount, const VkCopyDescriptorSet* pDescriptorCopies)
{
	VULKAN_ERR.println("Called vkUpdateDescriptorSets without proper driver PFN");
	return;
}
VkResult DevaFramework::internal::impldef_vkCreateFramebuffer(VkDevice device, const VkFramebufferCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkFramebuffer* pFramebuffer)
{
	VULKAN_ERR.println("Called vkCreateFramebuffer without proper driver PFN");
	return VK_SUCCESS;
}
void DevaFramework::internal::impldef_vkDestroyFramebuffer(VkDevice device, VkFramebuffer framebuffer, const VkAllocationCallbacks* pAllocator)
{
	VULKAN_ERR.println("Called vkDestroyFramebuffer without proper driver PFN");
	return;
}
VkResult DevaFramework::internal::impldef_vkCreateRenderPass(VkDevice device, const VkRenderPassCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass)
{
	VULKAN_ERR.println("Called vkCreateRenderPass without proper driver PFN");
	return VK_SUCCESS;
}
void DevaFramework::internal::impldef_vkDestroyRenderPass(VkDevice device, VkRenderPass renderPass, const VkAllocationCallbacks* pAllocator)
{
	VULKAN_ERR.println("Called vkDestroyRenderPass without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkGetRenderAreaGranularity(VkDevice device, VkRenderPass renderPass, VkExtent2D* pGranularity)
{
	VULKAN_ERR.println("Called vkGetRenderAreaGranularity without proper driver PFN");
	return;
}
VkResult DevaFramework::internal::impldef_vkCreateCommandPool(VkDevice device, const VkCommandPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCommandPool* pCommandPool)
{
	VULKAN_ERR.println("Called vkCreateCommandPool without proper driver PFN");
	return VK_SUCCESS;
}
void DevaFramework::internal::impldef_vkDestroyCommandPool(VkDevice device, VkCommandPool commandPool, const VkAllocationCallbacks* pAllocator)
{
	VULKAN_ERR.println("Called vkDestroyCommandPool without proper driver PFN");
	return;
}
VkResult DevaFramework::internal::impldef_vkResetCommandPool(VkDevice device, VkCommandPool commandPool, VkCommandPoolResetFlags flags)
{
	VULKAN_ERR.println("Called vkResetCommandPool without proper driver PFN");
	return VK_SUCCESS;
}
VkResult DevaFramework::internal::impldef_vkAllocateCommandBuffers(VkDevice device, const VkCommandBufferAllocateInfo* pAllocateInfo, VkCommandBuffer* pCommandBuffers)
{
	VULKAN_ERR.println("Called vkAllocateCommandBuffers without proper driver PFN");
	return VK_SUCCESS;
}
void DevaFramework::internal::impldef_vkFreeCommandBuffers(VkDevice device, VkCommandPool commandPool, uint32_t commandBufferCount, const VkCommandBuffer* pCommandBuffers)
{
	VULKAN_ERR.println("Called vkFreeCommandBuffers without proper driver PFN");
	return;
}
VkResult DevaFramework::internal::impldef_vkBeginCommandBuffer(VkCommandBuffer commandBuffer, const VkCommandBufferBeginInfo* pBeginInfo)
{
	VULKAN_ERR.println("Called vkBeginCommandBuffer without proper driver PFN");
	return VK_SUCCESS;
}
VkResult DevaFramework::internal::impldef_vkEndCommandBuffer(VkCommandBuffer commandBuffer)
{
	VULKAN_ERR.println("Called vkEndCommandBuffer without proper driver PFN");
	return VK_SUCCESS;
}
VkResult DevaFramework::internal::impldef_vkResetCommandBuffer(VkCommandBuffer commandBuffer, VkCommandBufferResetFlags flags)
{
	VULKAN_ERR.println("Called vkResetCommandBuffer without proper driver PFN");
	return VK_SUCCESS;
}
void DevaFramework::internal::impldef_vkCmdBindPipeline(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline)
{
	VULKAN_ERR.println("Called vkCmdBindPipeline without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkCmdSetViewport(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewport* pViewports)
{
	VULKAN_ERR.println("Called vkCmdSetViewport without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkCmdSetScissor(VkCommandBuffer commandBuffer, uint32_t firstScissor, uint32_t scissorCount, const VkRect2D* pScissors)
{
	VULKAN_ERR.println("Called vkCmdSetScissor without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkCmdSetLineWidth(VkCommandBuffer commandBuffer, float lineWidth)
{
	VULKAN_ERR.println("Called vkCmdSetLineWidth without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkCmdSetDepthBias(VkCommandBuffer commandBuffer, float depthBiasConstantFactor, float depthBiasClamp, float depthBiasSlopeFactor)
{
	VULKAN_ERR.println("Called vkCmdSetDepthBias without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkCmdSetBlendConstants(VkCommandBuffer commandBuffer, const float blendConstants[4])
{
	VULKAN_ERR.println("Called vkCmdSetBlendConstants without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkCmdSetDepthBounds(VkCommandBuffer commandBuffer, float minDepthBounds, float maxDepthBounds)
{
	VULKAN_ERR.println("Called vkCmdSetDepthBounds without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkCmdSetStencilCompareMask(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t compareMask)
{
	VULKAN_ERR.println("Called vkCmdSetStencilCompareMask without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkCmdSetStencilWriteMask(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t writeMask)
{
	VULKAN_ERR.println("Called vkCmdSetStencilWriteMask without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkCmdSetStencilReference(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t reference)
{
	VULKAN_ERR.println("Called vkCmdSetStencilReference without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkCmdBindDescriptorSets(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t firstSet, uint32_t descriptorSetCount, const VkDescriptorSet* pDescriptorSets, uint32_t dynamicOffsetCount, const uint32_t* pDynamicOffsets)
{
	VULKAN_ERR.println("Called vkCmdBindDescriptorSets without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkCmdBindIndexBuffer(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkIndexType indexType)
{
	VULKAN_ERR.println("Called vkCmdBindIndexBuffer without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkCmdBindVertexBuffers(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets)
{
	VULKAN_ERR.println("Called vkCmdBindVertexBuffers without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkCmdDraw(VkCommandBuffer commandBuffer, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance)
{
	VULKAN_ERR.println("Called vkCmdDraw without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkCmdDrawIndexed(VkCommandBuffer commandBuffer, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance)
{
	VULKAN_ERR.println("Called vkCmdDrawIndexed without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkCmdDrawIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride)
{
	VULKAN_ERR.println("Called vkCmdDrawIndirect without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkCmdDrawIndexedIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride)
{
	VULKAN_ERR.println("Called vkCmdDrawIndexedIndirect without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkCmdDispatch(VkCommandBuffer commandBuffer, uint32_t x, uint32_t y, uint32_t z)
{
	VULKAN_ERR.println("Called vkCmdDispatch without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkCmdDispatchIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset)
{
	VULKAN_ERR.println("Called vkCmdDispatchIndirect without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkCmdCopyBuffer(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferCopy* pRegions)
{
	VULKAN_ERR.println("Called vkCmdCopyBuffer without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkCmdCopyImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageCopy* pRegions)
{
	VULKAN_ERR.println("Called vkCmdCopyImage without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkCmdBlitImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageBlit* pRegions, VkFilter filter)
{
	VULKAN_ERR.println("Called vkCmdBlitImage without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkCmdCopyBufferToImage(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkBufferImageCopy* pRegions)
{
	VULKAN_ERR.println("Called vkCmdCopyBufferToImage without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkCmdCopyImageToBuffer(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferImageCopy* pRegions)
{
	VULKAN_ERR.println("Called vkCmdCopyImageToBuffer without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkCmdUpdateBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize dataSize, const void* pData)
{
	VULKAN_ERR.println("Called vkCmdUpdateBuffer without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkCmdFillBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize size, uint32_t data)
{
	VULKAN_ERR.println("Called vkCmdFillBuffer without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkCmdClearColorImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout imageLayout, const VkClearColorValue* pColor, uint32_t rangeCount, const VkImageSubresourceRange* pRanges)
{
	VULKAN_ERR.println("Called vkCmdClearColorImage without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkCmdClearDepthStencilImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout imageLayout, const VkClearDepthStencilValue* pDepthStencil, uint32_t rangeCount, const VkImageSubresourceRange* pRanges)
{
	VULKAN_ERR.println("Called vkCmdClearDepthStencilImage without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkCmdClearAttachments(VkCommandBuffer commandBuffer, uint32_t attachmentCount, const VkClearAttachment* pAttachments, uint32_t rectCount, const VkClearRect* pRects)
{
	VULKAN_ERR.println("Called vkCmdClearAttachments without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkCmdResolveImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageResolve* pRegions)
{
	VULKAN_ERR.println("Called vkCmdResolveImage without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkCmdSetEvent(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags stageMask)
{
	VULKAN_ERR.println("Called vkCmdSetEvent without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkCmdResetEvent(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags stageMask)
{
	VULKAN_ERR.println("Called vkCmdResetEvent without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkCmdWaitEvents(VkCommandBuffer commandBuffer, uint32_t eventCount, const VkEvent* pEvents, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, uint32_t memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier* pImageMemoryBarriers)
{
	VULKAN_ERR.println("Called vkCmdWaitEvents without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkCmdPipelineBarrier(VkCommandBuffer commandBuffer, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags, uint32_t memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier* pImageMemoryBarriers)
{
	VULKAN_ERR.println("Called vkCmdPipelineBarrier without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkCmdBeginQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, VkQueryControlFlags flags)
{
	VULKAN_ERR.println("Called vkCmdBeginQuery without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkCmdEndQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query)
{
	VULKAN_ERR.println("Called vkCmdEndQuery without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkCmdResetQueryPool(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount)
{
	VULKAN_ERR.println("Called vkCmdResetQueryPool without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkCmdWriteTimestamp(VkCommandBuffer commandBuffer, VkPipelineStageFlagBits pipelineStage, VkQueryPool queryPool, uint32_t query)
{
	VULKAN_ERR.println("Called vkCmdWriteTimestamp without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkCmdCopyQueryPoolResults(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize stride, VkQueryResultFlags flags)
{
	VULKAN_ERR.println("Called vkCmdCopyQueryPoolResults without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkCmdPushConstants(VkCommandBuffer commandBuffer, VkPipelineLayout layout, VkShaderStageFlags stageFlags, uint32_t offset, uint32_t size, const void* pValues)
{
	VULKAN_ERR.println("Called vkCmdPushConstants without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkCmdBeginRenderPass(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo* pRenderPassBegin, VkSubpassContents contents)
{
	VULKAN_ERR.println("Called vkCmdBeginRenderPass without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkCmdNextSubpass(VkCommandBuffer commandBuffer, VkSubpassContents contents)
{
	VULKAN_ERR.println("Called vkCmdNextSubpass without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkCmdEndRenderPass(VkCommandBuffer commandBuffer)
{
	VULKAN_ERR.println("Called vkCmdEndRenderPass without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkCmdExecuteCommands(VkCommandBuffer commandBuffer, uint32_t commandBufferCount, const VkCommandBuffer* pCommandBuffers)
{
	VULKAN_ERR.println("Called vkCmdExecuteCommands without proper driver PFN");
	return;
}
VkResult DevaFramework::internal::impldef_vkCreateSwapchainKHR(VkDevice device, const VkSwapchainCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchain)
{
	VULKAN_ERR.println("Called vkCreateSwapchainKHR without proper driver PFN");
	return VK_SUCCESS;
}
void DevaFramework::internal::impldef_vkDestroySwapchainKHR(VkDevice device, VkSwapchainKHR swapchain, const VkAllocationCallbacks* pAllocator)
{
	VULKAN_ERR.println("Called vkDestroySwapchainKHR without proper driver PFN");
	return;
}
VkResult DevaFramework::internal::impldef_vkGetSwapchainImagesKHR(VkDevice device, VkSwapchainKHR swapchain, uint32_t* pSwapchainImageCount, VkImage* pSwapchainImages)
{
	VULKAN_ERR.println("Called vkGetSwapchainImagesKHR without proper driver PFN");
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
VkResult DevaFramework::internal::impldef_vkCreateSharedSwapchainsKHR(VkDevice device, uint32_t swapchainCount, const VkSwapchainCreateInfoKHR* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchains)
{
	VULKAN_ERR.println("Called vkCreateSharedSwapchainsKHR without proper driver PFN");
	return VK_SUCCESS;
}
VkResult DevaFramework::internal::impldef_vkDebugMarkerSetObjectTagEXT(VkDevice device, VkDebugMarkerObjectTagInfoEXT* pTagInfo)
{
	VULKAN_ERR.println("Called vkDebugMarkerSetObjectTagEXT without proper driver PFN");
	return VK_SUCCESS;
}
VkResult DevaFramework::internal::impldef_vkDebugMarkerSetObjectNameEXT(VkDevice device, VkDebugMarkerObjectNameInfoEXT* pNameInfo)
{
	VULKAN_ERR.println("Called vkDebugMarkerSetObjectNameEXT without proper driver PFN");
	return VK_SUCCESS;
}
void DevaFramework::internal::impldef_vkCmdDebugMarkerBeginEXT(VkCommandBuffer commandBuffer, VkDebugMarkerMarkerInfoEXT* pMarkerInfo)
{
	VULKAN_ERR.println("Called vkCmdDebugMarkerBeginEXT without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkCmdDebugMarkerEndEXT(VkCommandBuffer commandBuffer)
{
	VULKAN_ERR.println("Called vkCmdDebugMarkerEndEXT without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkCmdDebugMarkerInsertEXT(VkCommandBuffer commandBuffer, VkDebugMarkerMarkerInfoEXT* pMarkerInfo)
{
	VULKAN_ERR.println("Called vkCmdDebugMarkerInsertEXT without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkCmdDrawIndirectCountAMD(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride)
{
	VULKAN_ERR.println("Called vkCmdDrawIndirectCountAMD without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkCmdDrawIndexedIndirectCountAMD(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride)
{
	VULKAN_ERR.println("Called vkCmdDrawIndexedIndirectCountAMD without proper driver PFN");
	return;
}
#ifdef VK_USE_PLATFORM_WIN32_KHR
VkResult DevaFramework::internal::impldef_vkGetMemoryWin32HandleNV(VkDevice device, VkDeviceMemory memory, VkExternalMemoryHandleTypeFlagsNV handleType, HANDLE* pHandle)
{
	VULKAN_ERR.println("Called vkGetMemoryWin32HandleNV without proper driver PFN");
	return VK_SUCCESS;
}
#endif
void DevaFramework::internal::impldef_vkCmdProcessCommandsNVX(VkCommandBuffer commandBuffer, const VkCmdProcessCommandsInfoNVX* pProcessCommandsInfo)
{
	VULKAN_ERR.println("Called vkCmdProcessCommandsNVX without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkCmdReserveSpaceForCommandsNVX(VkCommandBuffer commandBuffer, const VkCmdReserveSpaceForCommandsInfoNVX* pReserveSpaceInfo)
{
	VULKAN_ERR.println("Called vkCmdReserveSpaceForCommandsNVX without proper driver PFN");
	return;
}
VkResult DevaFramework::internal::impldef_vkCreateIndirectCommandsLayoutNVX(VkDevice device, const VkIndirectCommandsLayoutCreateInfoNVX* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkIndirectCommandsLayoutNVX* pIndirectCommandsLayout)
{
	VULKAN_ERR.println("Called vkCreateIndirectCommandsLayoutNVX without proper driver PFN");
	return VK_SUCCESS;
}
void DevaFramework::internal::impldef_vkDestroyIndirectCommandsLayoutNVX(VkDevice device, VkIndirectCommandsLayoutNVX indirectCommandsLayout, const VkAllocationCallbacks* pAllocator)
{
	VULKAN_ERR.println("Called vkDestroyIndirectCommandsLayoutNVX without proper driver PFN");
	return;
}
VkResult DevaFramework::internal::impldef_vkCreateObjectTableNVX(VkDevice device, const VkObjectTableCreateInfoNVX* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkObjectTableNVX* pObjectTable)
{
	VULKAN_ERR.println("Called vkCreateObjectTableNVX without proper driver PFN");
	return VK_SUCCESS;
}
void DevaFramework::internal::impldef_vkDestroyObjectTableNVX(VkDevice device, VkObjectTableNVX objectTable, const VkAllocationCallbacks* pAllocator)
{
	VULKAN_ERR.println("Called vkDestroyObjectTableNVX without proper driver PFN");
	return;
}
VkResult DevaFramework::internal::impldef_vkRegisterObjectsNVX(VkDevice device, VkObjectTableNVX objectTable, uint32_t objectCount, const VkObjectTableEntryNVX* const*    ppObjectTableEntries, const uint32_t* pObjectIndices)
{
	VULKAN_ERR.println("Called vkRegisterObjectsNVX without proper driver PFN");
	return VK_SUCCESS;
}
VkResult DevaFramework::internal::impldef_vkUnregisterObjectsNVX(VkDevice device, VkObjectTableNVX objectTable, uint32_t objectCount, const VkObjectEntryTypeNVX* pObjectEntryTypes, const uint32_t* pObjectIndices)
{
	VULKAN_ERR.println("Called vkUnregisterObjectsNVX without proper driver PFN");
	return VK_SUCCESS;
}
