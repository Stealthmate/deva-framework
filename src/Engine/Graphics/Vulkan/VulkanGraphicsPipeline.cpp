#include "VulkanPipeline.hpp"

using namespace DevaFramework;
using namespace DevaEngine;

VulkanGraphicsPipeline::VulkanGraphicsPipeline() noexcept {

}

VulkanGraphicsPipeline::VulkanGraphicsPipeline(VkPipeline handle, const VkGraphicsPipelineCreateInfo &cinfo)
	: mHandle(handle),
	mPipelineLayout(cinfo.layout) {
}

VkPipeline VulkanGraphicsPipeline::getHandle() const {
	return mHandle;
}

VkPipelineLayout VulkanGraphicsPipeline::getPipelineLayout() const {
	return mPipelineLayout;
}