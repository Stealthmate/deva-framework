#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_INSTANCE_FUNCTION_SET_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_INSTANCE_FUNCTION_SET_HPP

#include "Config.hpp"

namespace DevaFramework
{
	struct VulkanInstanceFunctionSet
	{
		DEVA_FRAMEWORK_API static VulkanInstanceFunctionSet load(VkInstance vkInstance);

		PFN_vkDestroyInstance                               vkDestroyInstance;

		PFN_vkEnumeratePhysicalDevices                      vkEnumeratePhysicalDevices;
		PFN_vkGetPhysicalDeviceFeatures                     vkGetPhysicalDeviceFeatures;
		PFN_vkGetPhysicalDeviceProperties                   vkGetPhysicalDeviceProperties;
		PFN_vkGetPhysicalDeviceQueueFamilyProperties        vkGetPhysicalDeviceQueueFamilyProperties;
		PFN_vkEnumerateDeviceExtensionProperties            vkEnumerateDeviceExtensionProperties;
		PFN_vkEnumerateDeviceLayerProperties                vkEnumerateDeviceLayerProperties;

		PFN_vkCreateDevice                                  vkCreateDevice;
		PFN_vkDestroyDevice                                 vkDestroyDevice;
		PFN_vkGetDeviceProcAddr                             vkGetDeviceProcAddr;


		PFN_vkGetPhysicalDeviceSurfaceSupportKHR            vkGetPhysicalDeviceSurfaceSupportKHR;
		PFN_vkGetPhysicalDeviceSurfaceFormatsKHR            vkGetPhysicalDeviceSurfaceFormatsKHR;
		PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR       vkGetPhysicalDeviceSurfaceCapabilitiesKHR;
		PFN_vkGetPhysicalDeviceSurfacePresentModesKHR       vkGetPhysicalDeviceSurfacePresentModesKHR;

#ifdef VK_USE_PLATFORM_WIN32_KHR		                   

		PFN_vkCreateWin32SurfaceKHR                         vkCreateWin32SurfaceKHR;
		PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR  vkGetPhysicalDeviceWin32PresentationSupportKHR;

#endif

		PFN_vkDestroySurfaceKHR                             vkDestroySurfaceKHR;
		PFN_vkCreateDebugReportCallbackEXT                  vkCreateDebugReportCallbackEXT;

		DEVA_FRAMEWORK_API VulkanInstanceFunctionSet();
		DEVA_FRAMEWORK_API VulkanInstanceFunctionSet(const VulkanInstanceFunctionSet &fset);
		DEVA_FRAMEWORK_API VulkanInstanceFunctionSet(VulkanInstanceFunctionSet &&fset);

		DEVA_FRAMEWORK_API VulkanInstanceFunctionSet& operator=(const VulkanInstanceFunctionSet &fset);
		DEVA_FRAMEWORK_API VulkanInstanceFunctionSet& operator=(VulkanInstanceFunctionSet &&fset);

		DEVA_FRAMEWORK_API ~VulkanInstanceFunctionSet();

	};
}

#endif //DEVA_FRAMEWORK_GRAPHICS_VULKAN_INSTANCE_FUNCTION_SET_HPP