#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_PIPELINE_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_PIPELINE_HPP

#include "Config.hpp"

namespace DevaFramework
{
	class VulkanPipelineBuilder {

	public:

		DEVA_FRAMEWORK_API VulkanPipelineBuilder& attachShaderStage(const VkPipelineShaderStageCreateInfo &shaderInfo);
		DEVA_FRAMEWORK_API VulkanPipelineBuilder& $();

	};
}

#endif //DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_PIPELINE_HPP