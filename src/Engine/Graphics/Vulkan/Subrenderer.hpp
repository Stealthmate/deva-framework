#ifndef DEVA_ENGINE_GRAPHICS_VULKAN_SUBRENDERER_HPP
#define DEVA_ENGINE_GRAPHICS_VULKAN_SUBRENDERER_HPP

#include "Config.hpp"
#include "VulkanRenderObject.hpp"
#include "VulkanQueueSubmitBuffer.hpp"

namespace DevaEngine {

	struct VulkanDrawableInfo {
		std::vector<VkBuffer> vertexBuffers;
		std::vector<VkDeviceSize> vertexOffsets;
		VkBuffer indexBuffer;
		VkDeviceSize indexOffset;
		VkIndexType indexType;
		VkBuffer mvpBuffer;
		VkDeviceSize mvpOffset;
		std::vector<VkDescriptorSet> descriptorSets;
		VkPipelineLayout pipelineLayout;
		VkPipelineBindPoint pipelineBindPoint;

		uint32_t indexCount;
		uint32_t instanceCount;
		uint32_t firstIndex;
		int32_t vertexOffset;
		uint32_t firstInstance;
	};

	struct VulkanRenderPassRecord {

		VkFramebuffer framebuffer;
		VkRenderPass renderPass;
		VkExtent2D renderArea;
		std::vector<VkClearValue> clearVals;
		VkPipeline pipeline;
		std::vector<VulkanDrawableInfo> objs;
	};

	namespace Vulkan {
		void renderPassRecord(const DevaFramework::VulkanDevice &device, VkCommandBuffer buffer, const VulkanRenderPassRecord &rp);
		VulkanDrawableInfo convertRenderObjectToDrawable(const VulkanRenderObject &vro);
	}
}

#endif //DEVA_ENGINE_GRAPHICS_VULKAN_SUBRENDERER_HPP