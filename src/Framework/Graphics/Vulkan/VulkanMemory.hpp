#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_MEMORY_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_MEMORY_HPP

#include "Config.hpp"
#include "VulkanBuffer.hpp"
#include "VulkanHandle.hpp"

namespace DevaFramework {

	class VulkanMemory {
	public:

		DEVA_FRAMEWORK_API static VulkanMemory allocate(VkDeviceSize size, uint32_t allocInfo);
		DEVA_FRAMEWORK_API static VulkanMemory forBuffer(const VulkanBuffer &buffer, const VulkanDevice &dev, VkMemoryPropertyFlags properties);

		DEVA_FRAMEWORK_API VulkanMemory() noexcept;
		DEVA_FRAMEWORK_API VulkanMemory(VulkanMemory &&memory) noexcept;
		DEVA_FRAMEWORK_API VulkanMemory& operator=(VulkanMemory &&memory) noexcept;

		DEVA_FRAMEWORK_API VkDeviceMemory handle() const noexcept { return mHandle; }
		DEVA_FRAMEWORK_API VkDeviceSize size() const noexcept { return mSize; }
		DEVA_FRAMEWORK_API VkMemoryType type() const noexcept { return mType; }

		DEVA_FRAMEWORK_API void free();

	private:

		VulkanHandle<VkDeviceMemory> mHandle;
		VkDeviceSize mSize;
		VkMemoryType mType;

		VulkanMemory(const VulkanDevice& dev, VkDeviceMemory memory, VkDeviceSize size, const VkMemoryType &type);
		VulkanMemory(const VulkanMemory &memory) = delete;
		VulkanMemory& operator=(const VulkanMemory &memory) = delete;
	};

}

#endif // DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_MEMORY_HPP