#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_DESCRIPTOR_SET_LAYOUT_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_DESCRIPTOR_SET_LAYOUT_HPP

#include "Config.hpp"

#include <unordered_map>
#include <unordered_set>

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

	struct VulkanDescriptorSet {
		VkDescriptorSet handle;
		VkDescriptorPool poolHandle;
	};

	struct VulkanDescriptorPool {
		VkDescriptorPool handle;
		std::vector<VulkanDescriptorSetLayout> supportedLayouts;
	};


	
	namespace Vulkan {

		DEVA_FRAMEWORK_API void destroyObject(const VulkanDevice &dev, VulkanDescriptorSetLayout &obj);
		DEVA_FRAMEWORK_API void destroyObject(const VulkanDevice &dev, VulkanDescriptorPool &obj);

		DEVA_FRAMEWORK_API VulkanDescriptorSetLayout createDescriptorSetLayout(
			const DevaFramework::VulkanDevice &dev,
			const std::vector<VkDescriptorSetLayoutBinding> &bindings,
			VkDescriptorSetLayoutCreateFlags flags);

		DEVA_FRAMEWORK_API VulkanDescriptorPool createDescriptorPool(
			const VulkanDevice &device,
			const std::vector<VulkanDescriptorSetLayout> &layouts,
			uint32_t maxSets);

		DEVA_FRAMEWORK_API std::vector<VulkanDescriptorSet> allocateDescriptorSets(
			const VulkanDevice &device,
			const VulkanDescriptorPool &pool,
			const std::vector<VkDescriptorSetLayout> &layouts,
			size_t count);

		DEVA_FRAMEWORK_API void freeDescriptorSets(
			const VulkanDevice &dev,
			const std::vector<VulkanDescriptorSet> &sets);
	}
}

#endif //DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_DESCRIPTOR_SET_LAYOUT_HPP