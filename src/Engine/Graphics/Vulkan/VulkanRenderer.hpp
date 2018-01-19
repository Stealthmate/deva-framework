#ifndef DEVA_ENGINE_VULKAN_RENDERER_HPP
#define DEVA_ENGINE_VULKAN_RENDERER_HPP

#include "Config.hpp"

#include "..\Renderer.hpp"
#include <DevaFramework/Graphics/Vulkan/VulkanInstance.hpp>
#include <DevaFramework/Graphics/Vulkan/VulkanDevice.hpp>
#include <DevaFramework/Graphics/Vulkan/VulkanCommandPool.hpp>
#include <DevaFramework/Graphics/Vulkan/VulkanBuffer.hpp>
#include <DevaFramework/Graphics/Vulkan/VulkanImage.hpp>
#include "VulkanRenderObject.hpp"
#include "VulkanBufferMemoryIndex.hpp"
#include "VulkanSwapchain.hpp"
#include "VulkanPipeline.hpp"
#include "VulkanQueueSubmitBuffer.hpp"
namespace DevaEngine
{

	class VulkanDescriptorSetLayout {
	public:
		struct LayoutModel {
			struct Binding {
				VkDescriptorType descriptorType;
				uint32_t descriptorCount;
			};
			std::unordered_map<uint32_t, Binding> bindings;
		};

		DEVA_ENGINE_API static VulkanDescriptorSetLayout create(
			const DevaFramework::VulkanDevice &device,
			const std::vector<VkDescriptorSetLayoutBinding> &bindings,
			VkDescriptorSetLayoutCreateFlags flags = 0);

		DEVA_ENGINE_API VkDescriptorSetLayout getHandle() const;
		DEVA_ENGINE_API const std::vector<VkDescriptorSetLayoutBinding>& getBindings() const;

		DEVA_ENGINE_API LayoutModel getLayoutModel() const;

	private:

		VulkanDescriptorSetLayout(VkDescriptorSetLayout handle);

		DevaFramework::VulkanHandle<VkDescriptorSetLayout> mHandle;
		std::vector<VkDescriptorSetLayoutBinding> mBindings;
	};

	class VulkanDescriptorPool {
	public:

		VulkanDescriptorPool(const DevaFramework::VulkanDevice &dev, const std::vector<VulkanDescriptorSetLayout::LayoutModel> &layouts, uint32_t maxSets);

		bool supportsLayout(const VulkanDescriptorSetLayout::LayoutModel &layout);

		std::vector<VkDescriptorSet> allocateDescriptorSets(const std::vector<VkDescriptorSetLayout> &layout, size_t count);
		void relinquishDescriptorSet(VkDescriptorSet dset);

		DEVA_ENGINE_API VkDescriptorPool getHandle() const;

	private:

		const DevaFramework::VulkanDevice& device;
		std::vector<VulkanDescriptorSetLayout::LayoutModel> supportedLayouts;
		VkDescriptorPool poolHandle;

	};

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

		DEVA_ENGINE_API virtual DevaFramework::Uuid loadImage(const DevaFramework::Image &img);

	private:

		class ImplSceneUpdateListener;
		friend class ImplSceneUpdateListener;

		std::shared_ptr<Scene::SceneUpdateObserver> sceneListener;
		std::unique_ptr<VulkanBufferMemoryIndex> bufmemIndex;

		std::shared_ptr<Scene> currentScene;

		std::unique_ptr<VulkanDescriptorPool> dpoolManager;

		DevaFramework::VulkanInstance instance;
		DevaFramework::VulkanDevice main_device;
		VkFence fence;
		VkColorSpaceKHR colorSpace;
		VkFormat colorFormat;

		DevaFramework::VulkanQueue renderQueue;

		DevaFramework::VulkanHandle<VkSurfaceKHR> surface;
		VulkanSwapchain swapchain;
		VulkanGraphicsPipeline pipeline;

		DevaFramework::VulkanCommandPool commandPool;
		std::vector<DevaFramework::VulkanCommandBuffer> commandBuffers;

		std::unordered_map<DevaFramework::Uuid, VulkanRenderObject> renderObjects;

		std::unordered_map<DevaFramework::Uuid, std::pair<VkDescriptorSetLayout, VulkanDescriptorSetLayout::LayoutModel>> dsLayouts;
		std::unordered_map<DevaFramework::Uuid, uint32_t> dsLayoutPipelineMap;

		std::unordered_map<DevaFramework::Uuid, DevaFramework::VulkanImage> mImages;

		VulkanQueueSubmitBuffer queueBuffer;

		void drawFrame();

		void loadDrawableObject(const SceneObjectID&id, const DrawableObject & object);
		void unloadModel(const SceneObjectID &id);
		void updateModelMVP(const SceneObjectID &id, const DevaFramework::mat4 &mvp);
	};
}


#endif //DEVA_ENGINE_VULKAN_RENDERER_HPP