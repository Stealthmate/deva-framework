#ifndef DEVA_ENGINE_VULKAN_RENDERER_HPP
#define DEVA_ENGINE_VULKAN_RENDERER_HPP

#include "Config.hpp"

#include "..\Renderer.hpp"
#include <DevaFramework/Graphics/Vulkan/VulkanInstance.hpp>
#include <DevaFramework/Graphics/Vulkan/VulkanDevice.hpp>
#include <DevaFramework/Graphics/Vulkan/VulkanCommandPool.hpp>
#include <DevaFramework/Graphics/Vulkan/VulkanBuffer.hpp>

#include "VulkanSwapchain.hpp"

namespace DevaEngine
{
	class VulkanRenderer : public Renderer
	{
		DevaFramework::VulkanInstance instance;
		DevaFramework::VulkanDevice main_device;

		VkColorSpaceKHR colorSpace;
		VkFormat colorFormat;

		unsigned int renderQueue;

		DevaFramework::VulkanHandle<VkSurfaceKHR> surface;
		VulkanSwapchain swapchain;
		DevaFramework::VulkanHandle<VkPipeline> pipeline;

		DevaFramework::VulkanCommandPool commandPool;
		std::vector<DevaFramework::VulkanBuffer> buffers;

		void drawFrame();

	public:

		DEVA_ENGINE_API VulkanRenderer();
		DEVA_ENGINE_API VulkanRenderer(const DevaFramework::Window &wnd);
		DEVA_ENGINE_API VulkanRenderer(VulkanRenderer &&renderer);

		DEVA_ENGINE_API virtual void attachToWindow(const DevaFramework::Window &wnd);
		DEVA_ENGINE_API virtual void createPipeline();

		DEVA_ENGINE_API virtual void renderExample();

		DEVA_ENGINE_API virtual void render(const Scene& scene);

		DEVA_ENGINE_API void destroy();
		DEVA_ENGINE_API virtual ~VulkanRenderer();
	};
}


#endif //DEVA_ENGINE_VULKAN_RENDERER_HPP