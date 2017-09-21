#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_BUFFER_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_BUFFER_HPP

#include "Config.hpp"
#include "VulkanHandle.hpp"
#include "../../Core/DataHolder.hpp"

namespace DevaFramework {

	//Immutable

	class VulkanBuffer {
	public:

		DEVA_FRAMEWORK_API static VulkanBuffer create(
			const VulkanDevice &dev, 
			VkBufferCreateFlags flags, 
			VkDeviceSize size, 
			VkBufferUsageFlags usage, 
			VkSharingMode sharingMode, 
			const std::vector<uint32_t> &queues = std::vector<uint32_t>());

		DEVA_FRAMEWORK_API VulkanBuffer();
		DEVA_FRAMEWORK_API VulkanBuffer(VulkanBuffer &&buffer);
		DEVA_FRAMEWORK_API VulkanBuffer& operator=(VulkanBuffer &&buffer);
		DEVA_FRAMEWORK_API ~VulkanBuffer();

		DEVA_FRAMEWORK_API VkBuffer handle() const noexcept { return mHandle; }
		DEVA_FRAMEWORK_API VkDeviceSize size() const noexcept { return mSize; }
		DEVA_FRAMEWORK_API VkBufferUsageFlags usage() const noexcept { return mUsage; }
		DEVA_FRAMEWORK_API VkSharingMode sharingMode() const noexcept { return mSharingMode; }
		DEVA_FRAMEWORK_API VkMemoryRequirements memoryRequirements() const noexcept { return mMemoryRequirements; }

	private:

		VkBuffer mHandle;
		VkDeviceSize mSize;
		VkBufferUsageFlags mUsage;
		VkSharingMode mSharingMode;
		VkMemoryRequirements mMemoryRequirements;

		VulkanBuffer(const VulkanBuffer& buffer) = delete;
		VulkanBuffer& operator=(const VulkanBuffer &buffer) = delete;
	};

}

#endif // DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_BUFFER_HPP