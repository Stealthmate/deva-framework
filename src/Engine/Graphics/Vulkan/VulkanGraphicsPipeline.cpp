#include "VulkanPipeline.hpp"

using namespace DevaFramework;
using namespace DevaEngine;

VulkanGraphicsPipeline::VulkanGraphicsPipeline() noexcept {

}

VulkanGraphicsPipeline::VulkanGraphicsPipeline(VulkanHandle<VkPipeline> handle, const VkGraphicsPipelineCreateInfo &cinfo)
	: mHandle(std::move(handle)) {
	VulkanHandle<VkPipelineLayout> layoutHandle;
	layoutHandle.replace(cinfo.layout);
	mPipelineLayout = std::move(layoutHandle);
}

VkPipeline VulkanGraphicsPipeline::getHandle() const {
	return mHandle;
}

VkPipelineLayout VulkanGraphicsPipeline::getPipelineLayout() const {
	return mPipelineLayout;
}