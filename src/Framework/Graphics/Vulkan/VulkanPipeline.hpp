#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_PIPELINE_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_PIPELINE_HPP

#include "Config.hpp"

namespace DevaFramework {
	struct VulkanDevice;


	struct VulkanGraphicsPipeline {
		VkPipeline handle;
		VkPipelineLayout layout;
		std::vector<VkDescriptorSetLayout> descSetLayouts;
	};

	namespace Vulkan {
		DEVA_FRAMEWORK_API void destroyObject(const VulkanDevice &dev, VulkanGraphicsPipeline &obj);
	}
}


#endif //DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_PIPELINE_HPP