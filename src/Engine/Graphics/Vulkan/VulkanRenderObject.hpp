#ifndef DEVA_ENGINE_GRAPHICS_VULKAN_VULKAN_RENDER_OBJECT_HPP
#define DEVA_ENGINE_GRAPHICS_VULKAN_VULKAN_RENDER_OBJECT_HPP

#include "Config.hpp"
#include "../DrawableObject.hpp"

namespace DevaEngine {

	class VulkanRenderObject {
	public:

		struct Offsets {
			VkDeviceSize mvp;
			VkDeviceSize vertex;
			VkDeviceSize index;
		};

		friend class VulkanRenderer;

		DEVA_ENGINE_API DevaFramework::Vulkan::VulkanBufferID buffer() const;
		DEVA_ENGINE_API uint32_t indexCount() const;
		DEVA_ENGINE_API Offsets offsets() const;
		DEVA_ENGINE_API VkDescriptorSet getDescriptorSet() const;

	private:

		VulkanRenderObject(
			const DevaFramework::Vulkan::VulkanBufferID &buffer, 
			uint32_t indexCount, 
			Offsets offsets,
			VkDescriptorSet dset);

		DevaFramework::Vulkan::VulkanBufferID mBufferVertexIndex;
		uint32_t mIndexCount;
		Offsets mOffsets;
		VkDescriptorSet mDescriptorSet;
	};

}


#endif // DEVA_ENGINE_GRAPHICS_VULKAN_VULKAN_RENDER_OBJECT_HPP