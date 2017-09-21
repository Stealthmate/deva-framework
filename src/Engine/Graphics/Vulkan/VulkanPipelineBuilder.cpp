#include "VulkanPipelineBuilder.hpp"

using namespace DevaFramework;
using namespace DevaEngine;

namespace {
	VkDescriptorSetLayoutBinding EMPTY_DESCRIPTOR_SET_LAYOUT_BINDING = {
		0,
		VK_DESCRIPTOR_TYPE_MAX_ENUM,
		0,
		0,
		0
	};
}

VulkanGraphicsPipelineBuilder::VulkanGraphicsPipelineBuilder()
{
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;
	scissor.offset = { 0, 0 };
	viewportCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	viewportCreateInfo.flags = 0;
	viewportCreateInfo.pNext = nullptr;
	viewportCreateInfo.viewportCount = 1;
	viewportCreateInfo.pViewports = &viewport;
	viewportCreateInfo.scissorCount = 1;
	viewportCreateInfo.pScissors = &scissor;

	inputAssemblyCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	inputAssemblyCreateInfo.primitiveRestartEnable = VK_FALSE;
	inputAssemblyCreateInfo.pNext = nullptr;
	inputAssemblyCreateInfo.flags = 0;

	rasterizerCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	rasterizerCreateInfo.pNext = nullptr;
	rasterizerCreateInfo.flags = 0;
	rasterizerCreateInfo.depthClampEnable = VK_FALSE;
	rasterizerCreateInfo.rasterizerDiscardEnable = VK_FALSE;
	rasterizerCreateInfo.polygonMode = VK_POLYGON_MODE_FILL;
	rasterizerCreateInfo.lineWidth = 1.0f;
	rasterizerCreateInfo.cullMode = VK_CULL_MODE_BACK_BIT;
	rasterizerCreateInfo.frontFace = VK_FRONT_FACE_CLOCKWISE;
	rasterizerCreateInfo.depthBiasEnable = VK_FALSE;
	rasterizerCreateInfo.depthBiasConstantFactor = 0.0f; // Optional
	rasterizerCreateInfo.depthBiasClamp = 0.0f; // Optional
	rasterizerCreateInfo.depthBiasSlopeFactor = 0.0f; // Optional

	multisamplingCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	multisamplingCreateInfo.sampleShadingEnable = VK_FALSE;
	multisamplingCreateInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
	multisamplingCreateInfo.minSampleShading = 1.0f; // Optional
	multisamplingCreateInfo.pSampleMask = nullptr; /// Optional
	multisamplingCreateInfo.alphaToCoverageEnable = VK_FALSE; // Optional
	multisamplingCreateInfo.alphaToOneEnable = VK_FALSE; // Optional
	multisamplingCreateInfo.pNext = nullptr;
	multisamplingCreateInfo.flags = 0;

	colorBlendAttachmentState.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	colorBlendAttachmentState.blendEnable = VK_FALSE;
	colorBlendAttachmentState.srcColorBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
	colorBlendAttachmentState.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
	colorBlendAttachmentState.colorBlendOp = VK_BLEND_OP_ADD; // Optional
	colorBlendAttachmentState.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
	colorBlendAttachmentState.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
	colorBlendAttachmentState.alphaBlendOp = VK_BLEND_OP_ADD; // Optional

	colorBlendCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	colorBlendCreateInfo.logicOpEnable = VK_FALSE;
	colorBlendCreateInfo.logicOp = VK_LOGIC_OP_COPY; // Optional
	colorBlendCreateInfo.attachmentCount = 1;
	colorBlendCreateInfo.pAttachments = &colorBlendAttachmentState;
	colorBlendCreateInfo.blendConstants[0] = 0.0f; // Optional
	colorBlendCreateInfo.blendConstants[1] = 0.0f; // Optional
	colorBlendCreateInfo.blendConstants[2] = 0.0f; // Optional
	colorBlendCreateInfo.blendConstants[3] = 0.0f; // Optional
	colorBlendCreateInfo.pNext = nullptr;
	colorBlendCreateInfo.flags = 0;

	dynamicStates = {
		VK_DYNAMIC_STATE_VIEWPORT,
		VK_DYNAMIC_STATE_LINE_WIDTH
	};

	dynamicStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	dynamicStateCreateInfo.dynamicStateCount = 2;
	dynamicStateCreateInfo.pDynamicStates = dynamicStates.data();

	createInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	createInfo.pNext = nullptr;
	createInfo.pVertexInputState = &vertexInputCreateInfo;
	createInfo.pInputAssemblyState = &inputAssemblyCreateInfo;
	createInfo.pTessellationState = nullptr;
	createInfo.pViewportState = &viewportCreateInfo;
	createInfo.pRasterizationState = &rasterizerCreateInfo;
	createInfo.pMultisampleState = &multisamplingCreateInfo;
	createInfo.pDepthStencilState = nullptr; // Optional
	createInfo.pColorBlendState = &colorBlendCreateInfo;
	createInfo.pDynamicState = nullptr; // Optional
	createInfo.flags = VK_PIPELINE_CREATE_DISABLE_OPTIMIZATION_BIT;
	createInfo.basePipelineIndex = 0;
	createInfo.basePipelineHandle = VK_NULL_HANDLE;

}

VulkanGraphicsPipelineBuilder& VulkanGraphicsPipelineBuilder::outputExtent(const VkExtent2D &extent) {

	viewport.width = (float)extent.width;
	viewport.height = (float)extent.height;

	scissor.extent = extent;

	return *this;
}

VulkanGraphicsPipelineBuilder& VulkanGraphicsPipelineBuilder::setTopology(VkPrimitiveTopology t)
{
	inputAssemblyCreateInfo.topology = t;

	return *this;
}

VulkanGraphicsPipelineBuilder& VulkanGraphicsPipelineBuilder::attachShader(VkShaderModule shader, VkShaderStageFlagBits type, const char* entry)
{
	VkPipelineShaderStageCreateInfo shaderStageInfo = {};
	shaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	shaderStageInfo.stage = type;
	shaderStageInfo.module = shader;
	shaderStageInfo.pName = "main";

	shaderStageCreateInfos.push_back(shaderStageInfo);

	ENGINE_LOG.v(strformat("Atttached shader {} to pipeline", (uintptr_t)shader));

	return *this;
}

VulkanGraphicsPipelineBuilder& VulkanGraphicsPipelineBuilder::setRenderPass(VkRenderPass rp, int subpass)
{
	createInfo.renderPass = rp;
	createInfo.subpass = subpass;

	return *this;
}

VulkanGraphicsPipeline VulkanGraphicsPipelineBuilder::build(const VulkanDevice &dev)
{
	auto device = dev.handle();
	auto & vk = dev.vk();

	VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutInfo.setLayoutCount = static_cast<uint32_t>(descriptorSetLayouts.size());// Optional
	pipelineLayoutInfo.pSetLayouts = descriptorSetLayouts.data(); // Optional
	pipelineLayoutInfo.pushConstantRangeCount = 0; // Optional
	pipelineLayoutInfo.pPushConstantRanges = 0; // Optional

	if (vk.vkCreatePipelineLayout(device, &pipelineLayoutInfo, nullptr,
		&createInfo.layout) != VK_SUCCESS) {
		throw DevaException("Failed to create pipeline layout!");
	}

	createInfo.pStages = shaderStageCreateInfos.data();
	createInfo.stageCount = (uint32_t)shaderStageCreateInfos.size();


	std::vector<VkVertexInputBindingDescription> bindingDescriptions;
	std::vector<VkVertexInputAttributeDescription> attrDescriptions;
	for (int i = 0;i < vertexBindings.size();i++)
	{
		auto & vib = vertexBindings[i];
		VkVertexInputBindingDescription bd;
		bd.binding = i;
		bd.inputRate = vib.inputRate();
		bd.stride = vib.stride();
		bindingDescriptions.push_back(bd);
		auto attrs = vib.attributes();
		attrDescriptions.insert(attrDescriptions.end(), attrs.begin(), attrs.end());
	}

	VkPipelineVertexInputStateCreateInfo inputState;
	inputState.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	inputState.pNext = nullptr;
	inputState.flags = 0;
	inputState.vertexBindingDescriptionCount = (uint32_t)bindingDescriptions.size();
	inputState.pVertexBindingDescriptions = bindingDescriptions.data();
	inputState.vertexAttributeDescriptionCount = (uint32_t)attrDescriptions.size();
	inputState.pVertexAttributeDescriptions = attrDescriptions.data();
	createInfo.pVertexInputState = &inputState;

	VulkanHandle<VkPipeline> pl(device, vk.vkDestroyPipeline);
	auto result = vk.vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &createInfo, nullptr, pl.replace());
	if (result != VK_SUCCESS) {
		throw DevaException("Failed to create graphics pipeline!");
	}

	//vk.vkDestroyPipelineLayout(device, createInfo.layout, nullptr);

	return VulkanGraphicsPipeline(std::move(pl), createInfo);
}

VulkanGraphicsPipelineBuilder& VulkanGraphicsPipelineBuilder::addVertexInputBinding(const DevaFramework::Vulkan::VertexInputBinding &binding)
{
	vertexBindings.push_back(binding);
	return *this;
}

VulkanGraphicsPipelineBuilder& VulkanGraphicsPipelineBuilder::addDescriptorSetLayout(VkDescriptorSetLayout layout, uint32_t *setn) {
	descriptorSetLayouts.push_back(layout);
	if (setn) *setn = descriptorSetLayouts.size() - 1;
	return *this;
}