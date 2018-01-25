#ifndef DEVA_ENGINE_VULKAN_RENDERER_HPP
#define DEVA_ENGINE_VULKAN_RENDERER_HPP

#include "Config.hpp"

#include "..\Renderer.hpp"
#include <DevaFramework/Graphics/Vulkan/VulkanInstance.hpp>
#include <DevaFramework/Graphics/Vulkan/VulkanDevice.hpp>
#include <DevaFramework/Graphics/Vulkan/VulkanCommandPool.hpp>
#include <DevaFramework/Graphics/Vulkan/VulkanBuffer.hpp>
#include <DevaFramework/Graphics/Vulkan/VulkanImage.hpp>
#include <DevaFramework\Graphics\Vulkan\VulkanRenderPass.hpp>
#include "VulkanRenderObject.hpp"
#include "VulkanBufferMemoryIndex.hpp"
#include "VulkanSwapchain.hpp"
#include "VulkanPipeline.hpp"
#include "VulkanQueueSubmitBuffer.hpp"
#include "Subrenderer.hpp"
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

	struct VulkanRendererCreateInfo {
		const DevaFramework::Window * wnd;
		std::vector<char*> extensions;
		std::vector<char*> layers;
	};

	class VulkanRenderAPI : public RenderAPI
	{
	public:

		DEVA_ENGINE_API VulkanRenderAPI();
		DEVA_ENGINE_API VulkanRenderAPI(const VulkanRendererCreateInfo &info);
		DEVA_ENGINE_API VulkanRenderAPI(VulkanRenderAPI &&renderer);
		DEVA_ENGINE_API virtual ~VulkanRenderAPI();

		DEVA_ENGINE_API void attachToWindow(const DevaFramework::Window &wnd);

		DEVA_ENGINE_API virtual void createPipeline();

		DEVA_ENGINE_API void destroy();

		DEVA_ENGINE_API virtual void onInit(const Preferences &prefs);
		DEVA_ENGINE_API virtual void onSetupRenderTargetWindow(const DevaFramework::Window &wnd);
		DEVA_ENGINE_API virtual void onSetupRenderTargetImage(const DevaFramework::Image &img);
		DEVA_ENGINE_API virtual ImageID loadImage(const DevaFramework::Image &img);
		DEVA_ENGINE_API virtual void drawScene();

		DEVA_ENGINE_API virtual void loadObject(const RenderObjectID &id, const RenderObject &ro);
		DEVA_ENGINE_API virtual void updateObjectMVP(const RenderObjectID &roid, const DevaFramework::mat4 &mvp);
		DEVA_ENGINE_API virtual void unloadObject(const RenderObjectID &roid);

	private:
		std::unique_ptr<VulkanBufferMemoryIndex> bufmemIndex;

		std::unique_ptr<VulkanDescriptorPool> dpoolManager;

		DevaFramework::VulkanInstance instance;
		DevaFramework::VulkanDevice main_device;
		VkFence fence;
		VkColorSpaceKHR colorSpace;
		VkFormat colorFormat;

		std::vector<VkFramebuffer> framebuffers;

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

		VulkanRenderPassRecord renderPassRecord;

		VkSemaphore imageAvailableSemaphore;
		VkSemaphore renderFinishedSemaphore;
		DevaFramework::VulkanRenderPass renderPass;

		void createRenderPass();


		void drawFrame();
	};
}


#endif //DEVA_ENGINE_VULKAN_RENDERER_HPP