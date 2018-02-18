#ifndef DEVA_ENGINE_VULKAN_RENDERER_HPP
#define DEVA_ENGINE_VULKAN_RENDERER_HPP

#include "Config.hpp"

#include "..\RenderAPI.hpp"
#include <DevaFramework/Graphics/Vulkan/VulkanInstance.hpp>
#include <DevaFramework/Graphics/Vulkan/VulkanDevice.hpp>
#include <DevaFramework/Graphics/Vulkan/VulkanCommandPool.hpp>
#include <DevaFramework\Graphics\Vulkan\VulkanRenderPass.hpp>
#include <DevaFramework\Graphics\Vulkan\VulkanDescriptorSet.hpp>
#include "VulkanRenderObject.hpp"
#include "VulkanBufferMemoryIndex.hpp"
#include "VulkanSwapchain.hpp"
#include <DevaFramework\Graphics\Vulkan\VulkanPipeline.hpp>
#include "VulkanQueueSubmitBuffer.hpp"
#include "VulkanPresenter.hpp"

namespace DevaEngine
{

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

		DEVA_ENGINE_API virtual RenderObjectID loadMesh(const DevaFramework::Mesh &mesh) override;
		DEVA_ENGINE_API virtual void unloadMesh(const RenderObjectID &id) override;
		DEVA_ENGINE_API virtual void setMeshMVP(const RenderObjectID &id, const DevaFramework::mat4 &mvp) override;

		DEVA_ENGINE_API virtual RenderObjectID loadTexture(const DevaFramework::Image &tex) override;
		DEVA_ENGINE_API virtual void unloadTexture(const RenderObjectID &id) override;

		DEVA_ENGINE_API virtual void bindMeshTexture(const RenderObjectID &meshid, const RenderObjectID &texid) override;
		DEVA_ENGINE_API virtual void unbindMeshTexture(const RenderObjectID &meshid, const RenderObjectID &texid) override;

	private:

		DevaFramework::VulkanInstance instance;
		DevaFramework::VulkanDevice main_device;
		std::unique_ptr<VulkanPresenter> presenter;
		DevaFramework::VulkanQueue renderQueue;

		std::vector<VkFramebuffer> framebuffers;

		DevaFramework::VulkanGraphicsPipeline pipeline;

		VulkanQueueSubmitBuffer queueBuffer;
		DevaFramework::VulkanRenderPass renderPass;
		VulkanRenderPassRecord renderPassRecord;

		DevaFramework::VulkanCommandPool commandPool;
		std::vector<DevaFramework::VulkanCommandBuffer> commandBuffers;

		VkSemaphore imageAvailableSemaphore;
		VkSemaphore renderFinishedSemaphore;
		VkFence fence;

		std::unique_ptr<VulkanBufferMemoryIndex> bufmemIndex;

		DevaFramework::VulkanDescriptorPool descPool;

		std::unordered_map<RenderObjectID, std::pair<VulkanMesh, VulkanMeshResources>> meshMap;
		std::unordered_map<RenderObjectID, std::pair<VulkanTexture, VulkanTextureResrouces>> texMap;

		std::unordered_map<DevaFramework::Uuid, std::pair<VkDescriptorSetLayout, DevaFramework::VulkanDescriptorSetLayout>> dsLayouts;
		std::unordered_map<DevaFramework::Uuid, uint32_t> descSetIndexMap;

		void createPipeline();
		void createRenderPass();
		void createFramebuffers();
	};
}


#endif //DEVA_ENGINE_VULKAN_RENDERER_HPP