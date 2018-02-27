#ifndef DEVA_ENGINE_API_GRAPHICS_VULKAN_VULKAN_MEMORY_MANAGER_HPP
#define DEVA_ENGINE_API_GRAPHICS_VULKAN_VULKAN_MEMORY_MANAGER_HPP

#include "Config.hpp"
#include <DevaFramework\Graphics\Vulkan\VulkanDevice.hpp>
#include <DevaFramework\Graphics\Vulkan\VulkanMemory.hpp>

namespace DevaFramework {
	struct VulkanMemoryRange;
	struct VulkanMemoryAlloc;
}

namespace DevaEngine {

	class BasicVulkanMemoryManager : public DevaFramework::IVulkanMemoryManager {
		typedef DevaFramework::VulkanMemoryAlloc Allocation;

	public:

		DEVA_ENGINE_API BasicVulkanMemoryManager(const DevaFramework::VulkanDevice &dev);

		DEVA_ENGINE_API virtual std::shared_ptr<const DevaFramework::VulkanMemoryRange> allocate(
			const VkMemoryRequirements &reqs,
			VkMemoryPropertyFlags properties) override;
		DEVA_ENGINE_API virtual void free(DevaFramework::VulkanMemoryRange &range) override;

	private:
		DevaFramework::VulkanDevice device;
	};
}

#endif //DEVA_ENGINE_API_GRAPHICS_VULKAN_VULKAN_MEMORY_MANAGER_HPP