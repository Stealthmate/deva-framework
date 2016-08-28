#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_INSTANCE_FUNCTION_SET_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_INSTANCE_FUNCTION_SET_HPP

#include "Config.hpp"

namespace DevaFramework
{
	struct InstanceFunctionSet
	{
		PFN_vkDestroyInstance                               vkDestroyInstance;

		PFN_vkEnumeratePhysicalDevices                      vkEnumeratePhysicalDevices;
		PFN_vkGetPhysicalDeviceFeatures                     vkGetPhysicalDeviceFeatures;
		PFN_vkGetPhysicalDeviceProperties                   vkGetPhysicalDeviceProperties;
		PFN_vkGetPhysicalDeviceQueueFamilyProperties        vkGetPhysicalDeviceQueueFamilyProperties;

		PFN_vkCreateDevice                                  vkCreateDevice;
		PFN_vkDestroyDevice                                 vkDestroyDevice;
		PFN_vkGetDeviceProcAddr                             vkGetDeviceProcAddr;


		PFN_vkGetPhysicalDeviceSurfaceSupportKHR            vkGetPhysicalDeviceSurfaceSupportKHR;
#ifdef VK_USE_PLATFORM_WIN32_KHR		                   

		PFN_vkCreateWin32SurfaceKHR                         vkCreateWin32SurfaceKHR;
		PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR  vkGetPhysicalDeviceWin32PresentationSupportKHR;

#endif

		PFN_vkDestroySurfaceKHR                             vkDestroySurfaceKHR;
		PFN_vkAcquireNextImageKHR                           vkAcquireNextImageKHR;

		DEVA_FRAMEWORK_API InstanceFunctionSet();
		DEVA_FRAMEWORK_API InstanceFunctionSet(const InstanceFunctionSet &fset);
		DEVA_FRAMEWORK_API InstanceFunctionSet(InstanceFunctionSet &&fset);

		DEVA_FRAMEWORK_API InstanceFunctionSet& operator=(const InstanceFunctionSet &fset);
		DEVA_FRAMEWORK_API InstanceFunctionSet& operator=(InstanceFunctionSet &&fset);

		DEVA_FRAMEWORK_API ~InstanceFunctionSet();

		DEVA_FRAMEWORK_API void load(VkInstance vkInstance);

	};
}

#endif //DEVA_FRAMEWORK_GRAPHICS_VULKAN_INSTANCE_FUNCTION_SET_HPP