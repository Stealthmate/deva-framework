#include "VulkanQueueSubmitBuffer.hpp"

using namespace DevaFramework;
using namespace DevaEngine;

void VulkanQueueSubmitBuffer::flush(const VulkanDevice &device, VkFence fence) {

	auto dev = device.handle;

	if (mQueue.parentDevice != dev) {
		throw DevaException("Attempt to flush queue from different device");
	}

	auto vk = device.vk;

	std::vector<VkSubmitInfo> submits;

	for(auto &cmd : mSubmitQueues) {
		VkSubmitInfo info;
		info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		info.pNext = nullptr;
		info.waitSemaphoreCount = cmd.waitSemaphores.size();
		info.pWaitSemaphores = cmd.waitSemaphores.data();
		info.pWaitDstStageMask = cmd.waitStages.data();
		info.commandBufferCount = cmd.buffers.size();
		info.pCommandBuffers = cmd.buffers.data();
		info.signalSemaphoreCount = cmd.signalSemaphores.size();
		info.pSignalSemaphores = cmd.signalSemaphores.data();
		submits.push_back(info);
	}

	VkResult res = vk.vkQueueSubmit(mQueue.handle, static_cast<uint32_t>(submits.size()), submits.data(), fence);
	if (res != VK_SUCCESS) {
		throw DevaException("Could not submit queue");
	}

	mSubmitQueues.clear();
}

void VulkanQueueSubmitBuffer::enqueue(
	const std::vector<VkCommandBuffer> &buffers,
	const std::vector<VkSemaphore> &waitSemaphores,
	const std::vector<VkPipelineStageFlags> &waitStages,
	const std::vector<VkSemaphore> &signalSemaphores) {

	VulkanQueueSubmitCommand cmd;
	cmd.buffers = buffers;
	cmd.waitSemaphores = waitSemaphores;
	cmd.waitStages = waitStages;
	cmd.signalSemaphores = signalSemaphores;

	mSubmitQueues.push_back(cmd);
}