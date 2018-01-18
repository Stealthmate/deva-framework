#ifndef DEVA_ENGINE_GRAPHICS_VULKAN_VULKAN_QUEUE_SUBMIT_BUFFER_HPP
#define DEVA_ENGINE_GRAPHICS_VULKAN_VULKAN_QUEUE_SUBMIT_BUFFER_HPP

#include"Config.hpp"
#include <DevaFramework\Graphics\Vulkan\VulkanDeviceQueue.hpp>
#include <DevaFramework\Graphics\Vulkan\VulkanCommandPool.hpp>
#include<deque>

namespace DevaEngine {

	struct VulkanQueueSubmitCommand {
		std::vector<VkSemaphore> waitSemaphores;
		std::vector<VkPipelineStageFlags> waitStages;
		std::vector<VkCommandBuffer> buffers;
		std::vector<VkSemaphore> signalSemaphores;
	};

	class VulkanQueueSubmitBuffer {
	public:

		DEVA_ENGINE_API VulkanQueueSubmitBuffer() : mQueue(VK_NULL_HANDLE) {}
		DEVA_ENGINE_API VulkanQueueSubmitBuffer(VkQueue queue) : mQueue(queue) {}

		DEVA_ENGINE_API void enqueue(
			const std::vector<VkCommandBuffer> &buffers,
			const std::vector<VkSemaphore> &waitSemaphores,
			const std::vector<VkPipelineStageFlags> &waitStages,
			const std::vector<VkSemaphore> &signalSemaphores
		);

		DEVA_ENGINE_API void flush(const DevaFramework::VulkanDevice &dev, VkFence fence);

	private:
		std::vector<VulkanQueueSubmitCommand> mSubmitQueues;
		VkQueue mQueue;
	};

}

#endif //DEVA_ENGINE_GRAPHICS_VULKAN_VULKAN_QUEUE_SUBMIT_BUFFER_HPP