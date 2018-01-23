#ifndef DEVA_ENGINE_GRAPHICS_VULKAN_SUBRENDERER_HPP
#define DEVA_ENGINE_GRAPHICS_VULKAN_SUBRENDERER_HPP

#include "Config.hpp"
#include "VulkanRenderObject.hpp"

namespace DevaEngine {

	struct VulkanDrawableInfo {
		std::vector<VkBuffer> vertexBuffers;
		std::vector<VkDeviceSize> vertexOffsets;
		VkBuffer indexBuffer;
		VkDeviceSize indexOffset;
		VkIndexType indexType;
		std::vector<VkDescriptorSet> descriptorSets;
		VkPipelineLayout pipelineLayout;
		VkPipelineBindPoint pipelineBindPoint;

		uint32_t indexCount;
		uint32_t instanceCount;
		uint32_t firstIndex;
		int32_t vertexOffset;
		uint32_t firstInstance;
	};

	struct VulkanRenderPass {

		VkFramebuffer framebuffer;
		VkRenderPass renderPass;
		VkExtent2D renderArea;
		std::vector<VkClearValue> clearVals;
		VkPipeline pipeline;

		void draw(
			const std::vector<VkBuffer> &vertexBuffers,
			const std::vector<VkDeviceSize> &vertexOffsets,
			VkBuffer indexBuffer,
			VkDeviceSize indexOffset,
			VkIndexType indexType,
			const std::vector<VkDescriptorSet> &descriptorSets,
			VkPipelineLayout pipelineLayout,
			VkPipelineBindPoint pipelineBindPoint) {
			VulkanDrawableInfo ro;
			ro.vertexBuffers = vertexBuffers;
			ro.vertexOffsets = vertexOffsets;
			ro.indexBuffer = indexBuffer;
			ro.indexOffset = indexOffset;
			ro.indexType = indexType;
			ro.descriptorSets = descriptorSets;
			ro.pipelineLayout = pipelineLayout;
			objs.push_back(ro);
		}

		std::vector<VulkanDrawableInfo> objs;
	};

	namespace Vulkan {
		void renderPassRecord(const DevaFramework::VulkanDevice &device, VkCommandBuffer buffer, const VulkanRenderPass &rp);
		VulkanDrawableInfo convertRenderObjectToDrawable(const VulkanRenderObject &vro);
	}
}

#endif //DEVA_ENGINE_GRAPHICS_VULKAN_SUBRENDERER_HPP