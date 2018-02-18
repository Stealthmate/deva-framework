#ifndef DEVA_ENGINE_GRAPHICS_VULKAN_SUBRENDERER_HPP
#define DEVA_ENGINE_GRAPHICS_VULKAN_SUBRENDERER_HPP

#include "Config.hpp"
#include <DevaFramework/Graphics/Vulkan/VulkanBuffer.hpp>
#include <DevaFramework\Graphics\Vulkan\VulkanDescriptorSet.hpp>
#include <DevaFramework/Graphics/Vulkan/VulkanImage.hpp>

namespace DevaEngine {

	struct VulkanMeshResources {
		std::vector<DevaFramework::Vulkan::VulkanBufferID> vertexBuffers;
		DevaFramework::Vulkan::VulkanBufferID indexBuffer;
		DevaFramework::Vulkan::VulkanBufferID mvpBuffer;
		std::vector<DevaFramework::VulkanDescriptorSet> descSets;
		size_t index;
	};

	struct VulkanMesh {
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

	struct VulkanTextureResrouces {
		VkDeviceMemory imgMemory;
		DevaFramework::VulkanImage img;
	};
	struct VulkanTexture {
		VkImageLayout layout;
		VkImageView imgView;
		VkSampler sampler;
	};

	struct VulkanRenderPassRecord {

		VkFramebuffer framebuffer;
		VkRenderPass renderPass;
		VkExtent2D renderArea;
		std::vector<VkClearValue> clearVals;
		VkPipeline pipeline;
		std::vector<VulkanMesh> objs;
	};

	namespace Vulkan {
		void recordRenderPass(const DevaFramework::VulkanDevice &device, VkCommandBuffer buffer, const VulkanRenderPassRecord &rp);
	}
}

#endif //DEVA_ENGINE_GRAPHICS_VULKAN_SUBRENDERER_HPP