#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_RENDER_PASS_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_RENDER_PASS_HPP

#include "Config.hpp"

namespace DevaFramework {

	struct VulkanRenderSubpass {
		VkPipelineBindPoint bindpoint;
		std::vector<VkAttachmentReference> attachmentRefs;
	};

	struct VulkanRenderPass {
		VkRenderPass handle;
		std::vector<VkAttachmentDescription> attachments;
		std::vector<VulkanRenderSubpass> subpasses;
		std::vector<VkSubpassDependency> dependencies;
	};

}

#endif //DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_RENDER_PASS_HPP