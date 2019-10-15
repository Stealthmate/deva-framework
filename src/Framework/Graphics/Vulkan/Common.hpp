#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_COMMON_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_COMMON_HPP

#include "Config.hpp"

#include "VulkanHandle.hpp"

#include <vector>
#include <functional>

namespace DevaFramework {

	struct VulkanInstance;
	struct VulkanDevice;
	struct VulkanBuffer;
	struct VulkanMemoryAlloc;
	struct VertexBuffer;

	class Window;

	namespace Vulkan
	{
		typedef VkBool32(VKAPI_CALL * VulkanDebugCallback)(
			VkDebugReportFlagsEXT,
			VkDebugReportObjectTypeEXT,
			uint64_t, size_t,
			int32_t,
			const char*,
			const char*,
			void*);

		DEVA_FRAMEWORK_API VkDebugReportCallbackEXT attachDebugCallback(
			const VulkanInstance &instance, 
			VulkanDebugCallback callback,
			VkDebugReportFlagsEXT flags, 
			void * userData = nullptr);

		DEVA_FRAMEWORK_API VulkanHandle<VkShaderModule> loadShaderFromFile(const VulkanDevice &dev, const char *filepath);
		DEVA_FRAMEWORK_API VkSurfaceKHR createSurfaceForWindow(const VulkanInstance &vkInstance, const Window &wnd);
		DEVA_FRAMEWORK_API std::vector<uint32_t> deviceQueueFamiliesSupportSurface(const VulkanInstance &vkInstance, VkPhysicalDevice pdev, VkSurfaceKHR surface);
		DEVA_FRAMEWORK_API std::vector<VkVertexInputAttributeDescription> getAttributeDescriptionsForVertexBuffer(
			const VertexBuffer &vb,
			const std::vector<uint32_t> &locations);

		DEVA_FRAMEWORK_API VkFence createFence(const VulkanDevice &dev, VkFenceCreateFlags flags);
		DEVA_FRAMEWORK_API VkSemaphore createSemaphore(const VulkanDevice &dev);

		template <class T>
		DEVA_FRAMEWORK_API T vulkanCopyHandle(const T &o1, const T &o2);

		DEVA_FRAMEWORK_API bool isBufferCompatibleWithMemory(const VulkanBuffer &buf, const VulkanMemoryAlloc &mem);

		DEVA_FRAMEWORK_API VkResult submitBuffers(VkQueue queue);

		DEVA_FRAMEWORK_API VkVertexInputAttributeDescription makeVAD(uint32_t location, uint32_t binding, VkFormat format, uint32_t offset);
	}

}

#endif //DEVA_FRAMEWORK_GRAPHICS_VULKAN_COMMON_HPP