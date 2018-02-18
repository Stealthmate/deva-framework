#ifndef DEVA_FRAMEWORK_VULKAN_PIPELINE_BUILDER_HPP
#define DEVA_FRAMEWORK_VULKAN_PIPELINE_BUILDER_HPP

#include "Config.hpp"
#include <DevaFramework\Util\CStructDeleter.hpp>
#include <DevaFramework\Graphics\Vulkan\VulkanHandle.hpp>
#include "VulkanSwapchain.hpp"

#include <DevaFramework\Graphics\Vulkan\VulkanVertexInputBinding.hpp>

namespace DevaFramework {
	struct VulkanGraphicsPipeline;
}

namespace DevaEngine {

	struct VulkanGraphicsPipelineBase {
		VkGraphicsPipelineCreateInfo create;

	};

	class VulkanGraphicsPipelineBuilder {
	public:
		DEVA_ENGINE_API VulkanGraphicsPipelineBuilder();


		DEVA_ENGINE_API VulkanGraphicsPipelineBuilder& outputExtent(const VkExtent2D &extent);
		DEVA_ENGINE_API VulkanGraphicsPipelineBuilder& setTopology(VkPrimitiveTopology t);
		DEVA_ENGINE_API VulkanGraphicsPipelineBuilder& setRenderPass(VkRenderPass rp, int subpass);

		DEVA_ENGINE_API VulkanGraphicsPipelineBuilder& attachShader(VkShaderModule shader, VkShaderStageFlagBits type, const char* entry);

		DEVA_ENGINE_API VulkanGraphicsPipelineBuilder& addVertexInputBinding(const DevaFramework::Vulkan::VertexInputBinding &binding);

		DEVA_ENGINE_API VulkanGraphicsPipelineBuilder& addDescriptorSetLayout(VkDescriptorSetLayout layout);

		DEVA_ENGINE_API DevaFramework::VulkanGraphicsPipeline build(const DevaFramework::VulkanDevice &dev);

	private:
		VkGraphicsPipelineCreateInfo createInfo;

		std::vector<VkPipelineShaderStageCreateInfo> shaderStageCreateInfos;

		VkPipelineVertexInputStateCreateInfo vertexInputCreateInfo;
		std::vector<DevaFramework::Vulkan::VertexInputBinding> vertexBindings;
		std::vector<VkVertexInputAttributeDescription> vertexInputAttributes;

		VkPipelineInputAssemblyStateCreateInfo inputAssemblyCreateInfo;

		VkPipelineRasterizationStateCreateInfo rasterizerCreateInfo;

		VkExtent2D extent;
		VkRect2D scissor;
		VkViewport viewport;
		VkPipelineViewportStateCreateInfo viewportCreateInfo;

		VkPipelineMultisampleStateCreateInfo multisamplingCreateInfo;

		VkPipelineColorBlendAttachmentState colorBlendAttachmentState;
		VkPipelineColorBlendStateCreateInfo colorBlendCreateInfo;

		std::vector<VkDynamicState> dynamicStates;
		VkPipelineDynamicStateCreateInfo dynamicStateCreateInfo;


		std::vector<VkDescriptorSetLayout> descriptorSetLayouts;

		void prepare();
	};
}

#endif //DEVA_FRAMEWORK_VULKAN_PIPELINE_BUILDER_HPP