#ifndef DEVA_FRAMEWORK_VULKAN_PIPELINE_BUILDER_HPP
#define DEVA_FRAMEWORK_VULKAN_PIPELINE_BUILDER_HPP

#include "Config.hpp"
#include <DevaFramework\Util\CStructDeleter.hpp>
#include "VulkanSwapchain.hpp"

namespace DevaEngine {

	class VulkanGraphicsPipelineBuilder {

		VkGraphicsPipelineCreateInfo createInfo;

		std::vector<VkPipelineShaderStageCreateInfo> shaderStageCreateInfos;

		VkPipelineVertexInputStateCreateInfo vertexInputCreateInfo;

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

		void prepare();

	public:
		DEVA_ENGINE_API VulkanGraphicsPipelineBuilder();


		DEVA_ENGINE_API VulkanGraphicsPipelineBuilder& outputExtent(const VkExtent2D &extent);
		DEVA_ENGINE_API VulkanGraphicsPipelineBuilder& setTopology(VkPrimitiveTopology t);
		DEVA_ENGINE_API VulkanGraphicsPipelineBuilder& setRenderPass(VkRenderPass rp, int subpass);
		DEVA_ENGINE_API VulkanGraphicsPipelineBuilder& setLayout(VkPipelineLayout layout);

		DEVA_ENGINE_API VulkanGraphicsPipelineBuilder& attachShader(VkShaderModule shader, VkShaderStageFlagBits type, const char* entry);

		DEVA_ENGINE_API VkPipeline build(const DevaFramework::VulkanDevice &dev);

	};
}

#endif //DEVA_FRAMEWORK_VULKAN_PIPELINE_BUILDER_HPP