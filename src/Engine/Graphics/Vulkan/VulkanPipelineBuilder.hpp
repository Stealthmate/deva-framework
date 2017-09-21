#ifndef DEVA_FRAMEWORK_VULKAN_PIPELINE_BUILDER_HPP
#define DEVA_FRAMEWORK_VULKAN_PIPELINE_BUILDER_HPP

#include "Config.hpp"
#include <DevaFramework\Util\CStructDeleter.hpp>
#include <DevaFramework\Graphics\Vulkan\VulkanHandle.hpp>
#include "VulkanSwapchain.hpp"
#include "VulkanPipeline.hpp"

#include <DevaFramework\Graphics\Vulkan\VertexInputBinding.hpp>

namespace DevaEngine {

	class VulkanGraphicsPipelineBuilder {
	public:
		DEVA_ENGINE_API VulkanGraphicsPipelineBuilder();


		DEVA_ENGINE_API VulkanGraphicsPipelineBuilder& outputExtent(const VkExtent2D &extent);
		DEVA_ENGINE_API VulkanGraphicsPipelineBuilder& setTopology(VkPrimitiveTopology t);
		DEVA_ENGINE_API VulkanGraphicsPipelineBuilder& setRenderPass(VkRenderPass rp, int subpass);

		DEVA_ENGINE_API VulkanGraphicsPipelineBuilder& attachShader(VkShaderModule shader, VkShaderStageFlagBits type, const char* entry);

		DEVA_ENGINE_API VulkanGraphicsPipelineBuilder& addVertexInputBinding(const DevaFramework::Vulkan::VertexInputBinding &binding);

		VkDescriptorSetLayoutBinding st;

		DEVA_ENGINE_API VulkanGraphicsPipelineBuilder& addDescriptorSetLayout(VkDescriptorSetLayout layout, uint32_t *setn = nullptr);

		DEVA_ENGINE_API VulkanGraphicsPipeline build(const DevaFramework::VulkanDevice &dev);

	private:
		VkGraphicsPipelineCreateInfo createInfo;

		std::vector<VkPipelineShaderStageCreateInfo> shaderStageCreateInfos;

		VkPipelineVertexInputStateCreateInfo vertexInputCreateInfo;
		std::vector<DevaFramework::Vulkan::VertexInputBinding> vertexBindings;
		std::vector<VkVertexInputBindingDescription> vertexInputBindings;
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