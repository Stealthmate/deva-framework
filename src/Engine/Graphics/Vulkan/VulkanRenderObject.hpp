#ifndef DEVA_ENGINE_GRAPHICS_VULKAN_VULKAN_RENDER_OBJECT_HPP
#define DEVA_ENGINE_GRAPHICS_VULKAN_VULKAN_RENDER_OBJECT_HPP

#include "Config.hpp"

namespace DevaEngine {

	class VulkanRenderObject {
	public:
		friend class VulkanRenderer;

		DEVA_ENGINE_API DevaFramework::Vulkan::VulkanBufferID buffer() const { return mBuffer; }
		DEVA_ENGINE_API VkDeviceSize offsetIndex() const { return mOffsetIndex; }
		DEVA_ENGINE_API uint32_t indexCount() const { return mIndexCount; }

	private:

		VulkanRenderObject(const DevaFramework::Vulkan::VulkanBufferID &buffer, VkDeviceSize offsetIndex, uint32_t indexCount) 
			: mBuffer(buffer), 
			mOffsetIndex(offsetIndex), 
			mIndexCount(indexCount) {}

		DevaFramework::Vulkan::VulkanBufferID mBuffer;
		VkDeviceSize mOffsetIndex;
		uint32_t mIndexCount;
	};

}


#endif // DEVA_ENGINE_GRAPHICS_VULKAN_VULKAN_RENDER_OBJECT_HPP