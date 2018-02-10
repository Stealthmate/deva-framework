#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_DESCRIPTOR_SET_LAYOUT_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_DESCRIPTOR_SET_LAYOUT_HPP

#include "Config.hpp"

#include <unordered_map>

namespace DevaFramework {

	struct VulkanDevice;


	struct VulkanDescriptorSetLayout {
		struct Binding {
			VkDescriptorType descriptorType;
			uint32_t descriptorCount;
		};

		std::unordered_map<uint32_t, Binding> bindings;
		VkDescriptorSetLayout handle;
	};

	namespace Vulkan {
		DEVA_FRAMEWORK_API VulkanDescriptorSetLayout createDescriptorSetLayout(
			const DevaFramework::VulkanDevice &dev,
			const std::vector<VkDescriptorSetLayoutBinding> &bindings,
			VkDescriptorSetLayoutCreateFlags flags);
	}

}

#endif //DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_DESCRIPTOR_SET_LAYOUT_HPP