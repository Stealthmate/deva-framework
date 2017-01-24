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
		VulkanGraphicsPipelineBuilder();


		VulkanGraphicsPipelineBuilder& outputExtent(const VkExtent2D &extent);
		VulkanGraphicsPipelineBuilder& setTopology(VkPrimitiveTopology t);
		VulkanGraphicsPipelineBuilder& setRenderPass(VkRenderPass rp, int subpass);
		VulkanGraphicsPipelineBuilder& setLayout(VkPipelineLayout layout);

		VulkanGraphicsPipelineBuilder& attachShader(VkShaderModule shader, VkShaderStageFlagBits type, const char* entry);

		DevaFramework::VulkanDeleter<VkPipeline> build(const DevaFramework::VulkanDevice &dev);

	};
}

#endif //DEVA_FRAMEWORK_VULKAN_PIPELINE_BUILDER_HPP