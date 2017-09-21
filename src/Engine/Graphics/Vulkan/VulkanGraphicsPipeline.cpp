#include "VulkanPipeline.hpp"

using namespace DevaFramework;
using namespace DevaEngine;

VulkanGraphicsPipeline::VulkanGraphicsPipeline() noexcept {

}

VulkanGraphicsPipeline::VulkanGraphicsPipeline(VkPipeline handle, const VkGraphicsPipelineCreateInfo &cinfo)
	: mHandle(handle) {
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