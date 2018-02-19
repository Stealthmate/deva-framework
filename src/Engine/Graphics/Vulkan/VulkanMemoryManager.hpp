#ifndef DEVA_ENGINE_API_GRAPHICS_VULKAN_VULKAN_MEMORY_MANAGER_HPP
#define DEVA_ENGINE_API_GRAPHICS_VULKAN_VULKAN_MEMORY_MANAGER_HPP

#include "Config.hpp"
#include <DevaFramework\Graphics\Vulkan\VulkanDevice.hpp>

namespace DevaFramework {
	struct VulkanMemory;
}

namespace DevaEngine {

	struct VulkanMemoryRange {
		VkDeviceMemory memory;
		VkDeviceSize offset;
		VkDeviceSize size;
	};

	class IVulkanMemoryManager {
	public:
		virtual std::shared_ptr<const VulkanMemoryRange> allocate(
			const VkMemoryRequirements &reqs,
			VkMemoryPropertyFlags properties) = 0;
		virtual void free(VulkanMemoryRange &range) = 0;
	};

	class BasicVulkanMemoryManager : public IVulkanMemoryManager {
		typedef DevaFramework::VulkanMemory Allocation;

	public:

		DEVA_ENGINE_API BasicVulkanMemoryManager(const DevaFramework::VulkanDevice &dev);

		DEVA_ENGINE_API virtual std::shared_ptr<const VulkanMemoryRange> allocate(
			const VkMemoryRequirements &reqs,
			VkMemoryPropertyFlags properties) override;
		DEVA_ENGINE_API virtual void free(VulkanMemoryRange &range) override;

	private:
		DevaFramework::VulkanDevice device;
	};

}

#endif //DEVA_ENGINE_API_GRAPHICS_VULKAN_VULKAN_MEMORY_MANAGER_HPP