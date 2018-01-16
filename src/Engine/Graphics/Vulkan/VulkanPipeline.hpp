#ifndef DEVA_ENGINE_VULKAN_PIPELINE_HPP
#define DEVA_ENGINE_VULKAN_PIPELINE_HPP

#include "Config.hpp"
#include <DevaFramework\Graphics\Vulkan\Config.hpp>

namespace DevaEngine
{
	class VulkanGraphicsPipeline {

	public:

		struct DescriptorBindingInfo {
			uint32_t binding;
			uint32_t count;
			VkDescriptorType type;
		};

		struct DescriptorSetLayoutInfo {
			std::vector<DescriptorBindingInfo> bindings;
		};

		DEVA_ENGINE_API VulkanGraphicsPipeline() noexcept;
		DEVA_ENGINE_API VulkanGraphicsPipeline(VkPipeline handle, const VkGraphicsPipelineCreateInfo &cinfo);

		DEVA_ENGINE_API VkPipeline getHandle() const;
		DEVA_ENGINE_API VkPipelineLayout getPipelineLayout() const;

	private:
		VkPipeline mHandle;
		VkPipelineLayout mPipelineLayout;
		std::vector<DescriptorSetLayoutInfo> mLayoutInfos;
	};
}

#endif //DEVA_ENGINE_VULKAN_PIPELINE_HPP