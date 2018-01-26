#include "VulkanRenderObject.hpp"

using namespace DevaFramework;
using namespace DevaEngine;

void DevaEngine::Vulkan::recordRenderPass(const VulkanDevice &device, VkCommandBuffer buffer, const VulkanRenderPassRecord &rp) {
	auto dev = device.handle;
	auto &vk = device.vk;

	VkRenderPassBeginInfo renderPassInfo = {};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	renderPassInfo.renderPass = rp.renderPass;
	renderPassInfo.framebuffer = rp.framebuffer;
	renderPassInfo.renderArea.offset = { 0, 0 };
	renderPassInfo.renderArea.extent = rp.renderArea;
	renderPassInfo.clearValueCount = rp.clearVals.size();
	renderPassInfo.pClearValues = rp.clearVals.data();
	vk.vkCmdBeginRenderPass(buffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
	vk.vkCmdBindPipeline(buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, rp.pipeline);

	for (auto &o : rp.objs) {
		vk.vkCmdBindVertexBuffers(buffer, 0, o.vertexBuffers.size(), o.vertexBuffers.data(), o.vertexOffsets.data());
		vk.vkCmdBindIndexBuffer(buffer, o.indexBuffer, o.indexOffset, o.indexType);
		vk.vkCmdBindDescriptorSets(buffer, o.pipelineBindPoint, o.pipelineLayout, 0, o.descriptorSets.size(), o.descriptorSets.data(), 0, nullptr);
		vk.vkCmdDrawIndexed(buffer, o.indexCount, o.instanceCount, o.firstIndex, o.vertexOffset, o.firstInstance);
	}

	vk.vkCmdEndRenderPass(buffer);
}