#ifndef DEVA_ENGINE_VULKAN_RENDERER_HPP
#define DEVA_ENGINE_VULKAN_RENDERER_HPP

#include "Config.hpp"

#include "..\Renderer.hpp"
#include <DevaFramework/Graphics/Vulkan/VulkanInstance.hpp>
#include <DevaFramework/Graphics/Vulkan/VulkanDevice.hpp>
#include <DevaFramework/Graphics/Vulkan/VulkanCommandPool.hpp>
#include <DevaFramework/Graphics/Vulkan/VulkanBuffer.hpp>
#include "VulkanRenderObject.hpp"
#include "VulkanBufferMemoryIndex.hpp"
#include "VulkanSwapchain.hpp"

namespace DevaEngine
{
	class VulkanRenderer : public Renderer
	{
	public:

		DEVA_ENGINE_API VulkanRenderer();
		DEVA_ENGINE_API VulkanRenderer(const DevaFramework::Window &wnd);
		DEVA_ENGINE_API VulkanRenderer(VulkanRenderer &&renderer);
		DEVA_ENGINE_API virtual ~VulkanRenderer();

		DEVA_ENGINE_API void attachToWindow(const DevaFramework::Window &wnd);

		DEVA_ENGINE_API virtual void createPipeline();

		DEVA_ENGINE_API virtual void renderExample() override;

		DEVA_ENGINE_API virtual std::shared_ptr<Scene> render(std::shared_ptr<Scene> scene) override;

		DEVA_ENGINE_API void destroy();


	private:

		class ImplSceneUpdateListener;
		friend class ImplSceneUpdateListener;

		std::shared_ptr<Scene::SceneUpdateObserver> sceneListener;
		std::unique_ptr<VulkanBufferMemoryIndex> bufmemIndex;

		std::shared_ptr<Scene> currentScene;

		DevaFramework::VulkanInstance instance;
		DevaFramework::VulkanDevice main_device;
		VkFence fence;
		VkColorSpaceKHR colorSpace;
		VkFormat colorFormat;

		unsigned int renderQueue;

		DevaFramework::VulkanHandle<VkSurfaceKHR> surface;
		VulkanSwapchain swapchain;
		DevaFramework::VulkanHandle<VkPipeline> pipeline;

		DevaFramework::VulkanCommandPool commandPool;

		std::unordered_map<DevaFramework::Uuid, VulkanRenderObject> renderObjects;

		void drawFrame();

		void loadModel(const SceneObjectID&id, const DevaFramework::Model &model);
		void unloadModel(const SceneObjectID &id);

		void freeBuffer(const DevaFramework::Vulkan::VulkanBufferID &buffer);

	};
}


#endif //DEVA_ENGINE_VULKAN_RENDERER_HPP