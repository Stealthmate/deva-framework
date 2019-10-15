#ifndef DEVA_ENGINE_GRAPHICS_VULKAN_VULKAN_PRESENTER_HPP
#define DEVA_ENGINE_GRAPHICS_VULKAN_VULKAN_PRESENTER_HPP

#include "Config.hpp"
#include <DevaFramework\Graphics\Vulkan\VulkanDevice.hpp>
#include <DevaFramework\Graphics\Vulkan\VulkanDeviceQueue.hpp>

#include "VulkanSwapchain.hpp"

namespace DevaEngine {

	class VulkanPresenter {
	public:

		DEVA_ENGINE_API VulkanPresenter(const DevaFramework::VulkanInstance &inst, const DevaFramework::Window &wnd);

		DEVA_ENGINE_API DevaFramework::VulkanDevice device() const;
		DEVA_ENGINE_API VulkanSwapchain swapchain() const;
		DEVA_ENGINE_API DevaFramework::VulkanQueue queue() const;
		DEVA_ENGINE_API DevaFramework::VulkanPhysicalDevice physicalDevice() const;
		DEVA_ENGINE_API std::vector<VkImageView> getAllImageViews() const;

		DEVA_ENGINE_API uint32_t nextImageIndex(uint64_t timeout, VkSemaphore sem, VkFence fence);
		DEVA_ENGINE_API void present(
			VkQueue queue,
			const std::vector<VkSemaphore> &waitSemaphores,
			uint32_t imageIndex);

	private:
		VulkanSwapchain mSwapchain;
		std::vector<VkImageView> mImageViews;
		DevaFramework::VulkanDevice mDev;
		VkFormat mFormat;
		DevaFramework::VulkanQueue mQueue;
	};



	namespace Vulkan {
		DEVA_ENGINE_API void present(
			const DevaFramework::VulkanDevice &dev,
			VkQueue queue,
			const std::vector<VkSemaphore> &waitSemaphores,
			const std::vector<VkSwapchainKHR> &swapchains,
			const std::vector<uint32_t> &imageIndices
		);
	}

}

#endif //DEVA_ENGINE_GRAPHICS_VULKAN_VULKAN_PRESENTER_HPP