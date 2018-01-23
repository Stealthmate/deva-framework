#include "Common.hpp"
#include "VulkanException.hpp"

#include "../../Util/Common.hpp"
#include "../../Window/Window.hpp"

using namespace DevaFramework;

namespace {

}

VulkanHandle<VkShaderModule> Vulkan::loadShaderFromFile(const VulkanDevice &dev, const char *filepath)
{
	auto src = readBinaryFile(filepath);
	VkShaderModuleCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = src.size();
	createInfo.pCode = (uint32_t*)src.buf().data();

	auto& vk = dev.vk;

	VulkanHandle<VkShaderModule> shaderModule(dev.handle, dev.vk.vkDestroyShaderModule);

	if (vk.vkCreateShaderModule(dev.handle, &createInfo, nullptr, shaderModule.replace()) != VK_SUCCESS) {
		throw DevaException("failed to create shader module!");
	}

	LOG.v(strformat("Load shader file \"{}\" with id: {}", filepath, (uintptr_t)shaderModule.handle()));

	return shaderModule;
}

VulkanHandle<VkSurfaceKHR> Vulkan::createSurfaceFromWindow(const VulkanInstance &vkInstance, const Window &wnd)
{
	auto os = wnd.getOSHandles();
#ifdef VK_USE_PLATFORM_WIN32_KHR
	VkWin32SurfaceCreateInfoKHR surface_cinfo =
	{
		VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR,
		nullptr,
		0,
		(HINSTANCE)os->win32_hinstance(),
		(HWND)os->win32_hwnd()
	};
#endif
#ifdef VK_USE_PLATFORM_WAYLAND_KHR
#error WAYLAND NOT IMPLEMENTED!
#endif
#ifdef VK_USE_PLATFORM_XLIB_KHR
#error XLIB NOT IMPLEMENTED!
#endif
#ifdef VK_USE_PLATFORM_XCB_KHR
#error XCB NOT IMPLEMENTED!
#endif
#ifdef VK_USE_PLATFORM_MIR_KHR
#error MIR NOT IMPLEMENTED!
#endif
#ifdef VK_USE_PLATFORM_ANDROID_KHR
#error ANDROID NOT IMPLEMENTED!
#endif

	VulkanHandle<VkSurfaceKHR> surface(vkInstance.handle, vkInstance.vk.vkDestroySurfaceKHR);
	vkInstance.vk.vkCreateWin32SurfaceKHR(vkInstance.handle, &surface_cinfo, nullptr, surface.replace());
	return surface;
}


std::vector<uint32_t> Vulkan::deviceQueueFamiliesSupportSurface(const VulkanInstance &vkInstance, VkPhysicalDevice handle, VkSurfaceKHR surface)
{
	auto &vk = vkInstance.vk;
	auto pdev = Vulkan::getPhysicalDeviceStruct(vkInstance, handle);
	std::vector<uint32_t> queues;
	for (int i = 0;i < pdev.queueFamilyProperties.size();i++)
	{
		auto& q = pdev.queueFamilyProperties[i];
		if ((q.queueFlags & VK_QUEUE_GRAPHICS_BIT) == 0) continue;

		VkBool32 supportsPresent;
		vk.vkGetPhysicalDeviceSurfaceSupportKHR(pdev.handle,
			i,
			surface,
			&supportsPresent);
		if (supportsPresent == VK_TRUE) {
			queues.push_back(i);
		}
	}

	return queues;
}

VulkanHandle<VkSemaphore> Vulkan::createSemaphore(const VulkanDevice &dev) {

	auto device = dev.handle;
	auto &vk = dev.vk;

	VkSemaphoreCreateInfo semaphoreInfo = {};
	semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
	semaphoreInfo.pNext = nullptr;
	semaphoreInfo.flags = 0;
	VulkanHandle<VkSemaphore> sem(device, vk.vkDestroySemaphore);
	VkResult result = vk.vkCreateSemaphore(device, &semaphoreInfo, nullptr, sem.replace());
	if (result != VK_SUCCESS) {
		throw DevaException("Could not create semaphore!");
	}

	return sem;
}

bool Vulkan::isBufferCompatibleWithMemory(const VulkanBuffer &buf, const VulkanMemory &mem) {
	auto req = buf.memoryRequirements;
	
	if (req.size > mem.size) return false;
	if (req.memoryTypeBits & (1 << mem.typeIndex == 0)) return false;

	return true;
}

VkVertexInputAttributeDescription Vulkan::makeVAD(uint32_t location, uint32_t binding, VkFormat format, uint32_t offset)
{
	VkVertexInputAttributeDescription vad;
	vad.location = location;
	vad.binding = binding;
	vad.format = format;
	vad.offset = offset;

	return vad;
}
