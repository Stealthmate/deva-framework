#ifndef DEVA_ENGINE_VULKAN_RENDERER_HPP
#define DEVA_ENGINE_VULKAN_RENDERER_HPP

#include "Config.hpp"

#include "Renderer.hpp"
#include <DevaFramework/Graphics/Vulkan/VulkanInstance.hpp>
#include <DevaFramework/Graphics/Vulkan/VulkanDevice.hpp>

#include "VulkanSwapchain.hpp"

namespace DevaEngine
{
	class VulkanRenderer : public Renderer
	{

		DevaFramework::VulkanInstance instance;
		DevaFramework::VulkanPhysicalDeviceWrapper main_pdev;
		DevaFramework::VulkanDevice main_device;

		VkColorSpaceKHR colorSpace;
		VkFormat colorFormat;

		unsigned int renderQueue;

		VkSurfaceKHR surface;
		VulkanSwapchain swapchain;
		VkPipeline pipeline;
		void drawFrame();

	public:

		DEVA_ENGINE_API VulkanRenderer();
		DEVA_ENGINE_API VulkanRenderer(const DevaFramework::Window &wnd);

		DEVA_ENGINE_API virtual void attachToWindow(const DevaFramework::Window &wnd);
		DEVA_ENGINE_API virtual void createPipeline();

		DEVA_ENGINE_API virtual void renderExample();

	};
}


#endif //DEVA_ENGINE_VULKAN_RENDERER_HPP