#ifndef DEVA_ENGINE_GRAPHICS_VULKAN_VULKAN_RENDER_OBJECT_HPP
#define DEVA_ENGINE_GRAPHICS_VULKAN_VULKAN_RENDER_OBJECT_HPP

#include "Config.hpp"
#include "../DrawableObject.hpp"

namespace DevaEngine {

	class VulkanDescriptorSet {
	public:

	private:

		VkDescriptorSet handle;
		VkDescriptorSetLayout layoutHandle;
	};

	class VulkanRenderObject {
	public:

		friend class VulkanRenderer;

		DEVA_ENGINE_API DevaFramework::Vulkan::VulkanBufferID buffer() const;
		DEVA_ENGINE_API VkDeviceSize offsetIndex() const;
		DEVA_ENGINE_API uint32_t indexCount() const;
		DEVA_ENGINE_API DevaFramework::Vulkan::VulkanBufferID bufferMVP() const;
		DEVA_ENGINE_API VkDeviceSize offsetMVP() const;
		DEVA_ENGINE_API VkDescriptorSet getDescriptorSet() const;

	private:

		VulkanRenderObject(
			const DevaFramework::Vulkan::VulkanBufferID &buffer, 
			VkDeviceSize offsetIndex, 
			uint32_t indexCount, 
			VkDeviceSize offsetMVP,
			VkDescriptorSet dset);

		DevaFramework::Vulkan::VulkanBufferID mBufferVertexIndex;
		uint32_t mIndexCount;
		VkDeviceSize mOffsetIndex;

		DevaFramework::Vulkan::VulkanBufferID mBufferMVP;
		VkDeviceSize mOffsetMVP;

		VkDescriptorSet dset;
	};

}


#endif // DEVA_ENGINE_GRAPHICS_VULKAN_VULKAN_RENDER_OBJECT_HPP