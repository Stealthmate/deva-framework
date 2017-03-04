#include "Common.hpp"
#include "VulkanException.hpp"

#include "../../Util/Common.hpp"
#include "../../Window/Window.hpp"

using namespace DevaFramework;

namespace {

}

VkShaderModule Vulkan::loadShaderFromFile(const VulkanDevice &dev, const char *filepath)
{
	auto src = readBinaryFile(filepath);

	VkShaderModuleCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = src.size();
	createInfo.pCode = (uint32_t*)src.buf().data();

	auto& vk = dev.vk();

	VkShaderModule shaderModule;

	if (vk.vkCreateShaderModule(dev.handle(), &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
		throw DevaException("failed to create shader module!");
	}

	return shaderModule;
}

VkSurfaceKHR Vulkan::createSurfaceFromWindow(const VulkanInstance &vkInstance, const Window &wnd)
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

	VkSurfaceKHR surface;
	vkInstance.vk().vkCreateWin32SurfaceKHR(vkInstance.handle(), &surface_cinfo, nullptr, &surface);
	return surface;
}


std::vector<uint32_t> Vulkan::deviceQueueFamiliesSupportSurface(const VulkanInstance &vkInstance, VkPhysicalDevice handle, VkSurfaceKHR surface)
{
	auto &vk = vkInstance.vk();
	auto pdev = VulkanPhysicalDeviceWrapper::fromHandle(vkInstance, handle);
	std::vector<uint32_t> queues;
	for (int i = 0;i < pdev.queueFamilies.size();i++)
	{
		auto& q = pdev.queueFamilies[i];
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