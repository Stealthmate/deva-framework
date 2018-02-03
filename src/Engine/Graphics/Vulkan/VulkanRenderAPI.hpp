#ifndef DEVA_ENGINE_VULKAN_RENDERER_HPP
#define DEVA_ENGINE_VULKAN_RENDERER_HPP

#include "Config.hpp"

#include "..\RenderAPI.hpp"
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
#include "VulkanPresenter.hpp"

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

	struct VulkanMeshResources {
		std::vector<DevaFramework::Vulkan::VulkanBufferID> vertexBuffers;
		DevaFramework::Vulkan::VulkanBufferID indexBuffer;
		DevaFramework::Vulkan::VulkanBufferID mvpBuffer;
		size_t index;
	};

	class UpdateStager {
	public:
		struct PrebufInfo {
			VkDeviceSize srcOffset;
			VkDeviceSize size;
			VkBuffer dst;
			VkDeviceSize dstOffset;
		};

		void stageUpdate(
			const DevaFramework::VulkanDevice &device,
			void * srcData,
			VkDeviceSize dataSize,
			VkBuffer dst,
			VkDeviceSize dstOffset
		);

		void recordFlush(const DevaFramework::VulkanDevice &device, VkCommandBuffer buffer);

		VkDeviceSize sizeLeft() const;

	private:

		std::vector<PrebufInfo> queue;

		VkBuffer prebuffer;
		VkDeviceMemory memory;
		VkDeviceSize capacity;
		VkDeviceSize usedCap;
	};

	class VulkanRenderAPI : public RenderAPI
	{
	public:

		DEVA_ENGINE_API virtual void onInit(const Preferences &prefs) override;
		DEVA_ENGINE_API virtual void onSetupRenderTargetWindow(const DevaFramework::Window &wnd) override;
		DEVA_ENGINE_API virtual void onSetupRenderTargetImage(const DevaFramework::Image &img) override;
		DEVA_ENGINE_API virtual void onDestroy() override;

		DEVA_ENGINE_API virtual void drawScene() override;

		DEVA_ENGINE_API virtual ImageID loadImage(const DevaFramework::Image &img);

		DEVA_ENGINE_API virtual RenderObjectID loadMesh(const DevaFramework::Mesh &mesh) override;
		DEVA_ENGINE_API virtual void unloadMesh(const RenderObjectID &id) override;
		DEVA_ENGINE_API virtual void setMeshMVP(const RenderObjectID &id, const DevaFramework::mat4 &mvp) override;

		DEVA_ENGINE_API virtual RenderObjectID loadTexture(const DevaFramework::Image &tex) override;
		DEVA_ENGINE_API virtual void unloadTexture(const RenderObjectID &id) override;

		DEVA_ENGINE_API virtual void bindMeshTexture(const RenderObjectID &meshid, const RenderObjectID &texid) override;
		DEVA_ENGINE_API virtual void unbindMeshTexture(const RenderObjectID &meshid, const RenderObjectID &texid) override;

	private:
		std::unique_ptr<VulkanBufferMemoryIndex> bufmemIndex;

		std::unique_ptr<VulkanDescriptorPool> dpoolManager;

		DevaFramework::VulkanInstance instance;
		DevaFramework::VulkanDevice main_device;
		VkFence fence;

		std::vector<VkFramebuffer> framebuffers;

		DevaFramework::VulkanQueue renderQueue;
		VulkanGraphicsPipeline pipeline;

		DevaFramework::Vulkan::VulkanBufferID prebuffer;

		DevaFramework::VulkanCommandPool commandPool;
		std::vector<DevaFramework::VulkanCommandBuffer> commandBuffers;

		std::unordered_map<RenderObjectID, std::pair<VulkanMesh, VulkanMeshResources>> meshMap;
		std::unordered_map<RenderObjectID, std::pair<VulkanTexture, VulkanTextureResrouces>> texMap;
		std::vector<VkSemaphore> objectUpdateSemaphores;

		std::unordered_map<DevaFramework::Uuid, std::pair<VkDescriptorSetLayout, VulkanDescriptorSetLayout::LayoutModel>> dsLayouts;
		std::unordered_map<DevaFramework::Uuid, uint32_t> dsLayoutPipelineMap;

		std::unordered_map<DevaFramework::Uuid, DevaFramework::VulkanImage> mImages;

		VulkanQueueSubmitBuffer queueBuffer;

		VulkanRenderPassRecord renderPassRecord;

		VkSemaphore imageAvailableSemaphore;
		VkSemaphore renderFinishedSemaphore;
		DevaFramework::VulkanRenderPass renderPass;
		std::unique_ptr<VulkanPresenter> presenter;

		void createPipeline();
		void createRenderPass();
		void createFramebuffers();
		void attachToWindow(const DevaFramework::Window &wnd);
	};
}


#endif //DEVA_ENGINE_VULKAN_RENDERER_HPP