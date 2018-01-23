#ifndef DEVA_ENGINE_GRAPHICS_VULKAN_VULKAN_PRESENTER_HPP
#define DEVA_ENGINE_GRAPHICS_VULKAN_VULKAN_PRESENTER_HPP

#include "Config.hpp"
#include <DevaFramework\Graphics\Vulkan\VulkanDevice.hpp>

namespace DevaFramework {

	namespace Vulkan {
		DEVA_ENGINE_API void present(
			const VulkanDevice &dev, 
			VkQueue queue,
			const std::vector<VkSemaphore> &waitSemaphores,
			const std::vector<VkSwapchainKHR> &swapchains,
			const std::vector<uint32_t> &imageIndices
		) {

			VkPresentInfoKHR info = {};
			info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

			info.waitSemaphoreCount = waitSemaphores.size();
			info.pWaitSemaphores = waitSemaphores.data();
			info.swapchainCount = swapchains.size();
			info.pSwapchains = swapchains.data();
			info.pImageIndices = imageIndices.data();
			info.pResults = nullptr; // Optional

			dev.vk.vkQueuePresentKHR(queue, &info);
		}
	}

}

#endif //DEVA_ENGINE_GRAPHICS_VULKAN_VULKAN_PRESENTER_HPP