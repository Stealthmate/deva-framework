#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_INSTANCE_FUNCTION_SET_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_INSTANCE_FUNCTION_SET_HPP

#include "Config.hpp"

namespace DevaFramework
{
	struct VulkanInstanceFunctionSet
	{
		DEVA_FRAMEWORK_API static VulkanInstanceFunctionSet load(VkInstance vkInstance);

		PFN_vkGetDeviceProcAddr                                         vkGetDeviceProcAddr;
		PFN_vkDestroyInstance                                           vkDestroyInstance;
		PFN_vkEnumeratePhysicalDevices                                  vkEnumeratePhysicalDevices;
		PFN_vkGetPhysicalDeviceFeatures                                 vkGetPhysicalDeviceFeatures;
		PFN_vkGetPhysicalDeviceFormatProperties                         vkGetPhysicalDeviceFormatProperties;
		PFN_vkGetPhysicalDeviceImageFormatProperties                    vkGetPhysicalDeviceImageFormatProperties;
		PFN_vkGetPhysicalDeviceProperties                               vkGetPhysicalDeviceProperties;
		PFN_vkGetPhysicalDeviceQueueFamilyProperties                    vkGetPhysicalDeviceQueueFamilyProperties;
		PFN_vkGetPhysicalDeviceMemoryProperties                         vkGetPhysicalDeviceMemoryProperties;
		PFN_vkCreateDevice                                              vkCreateDevice;
		PFN_vkEnumerateDeviceExtensionProperties                        vkEnumerateDeviceExtensionProperties;
		PFN_vkEnumerateDeviceLayerProperties                            vkEnumerateDeviceLayerProperties;
		PFN_vkGetPhysicalDeviceSparseImageFormatProperties              vkGetPhysicalDeviceSparseImageFormatProperties;
		PFN_vkDestroySurfaceKHR                                         vkDestroySurfaceKHR;
		PFN_vkGetPhysicalDeviceSurfaceSupportKHR                        vkGetPhysicalDeviceSurfaceSupportKHR;
		PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR                   vkGetPhysicalDeviceSurfaceCapabilitiesKHR;
		PFN_vkGetPhysicalDeviceSurfaceFormatsKHR                        vkGetPhysicalDeviceSurfaceFormatsKHR;
		PFN_vkGetPhysicalDeviceSurfacePresentModesKHR                   vkGetPhysicalDeviceSurfacePresentModesKHR;
		PFN_vkGetPhysicalDeviceDisplayPropertiesKHR                     vkGetPhysicalDeviceDisplayPropertiesKHR;
		PFN_vkGetPhysicalDeviceDisplayPlanePropertiesKHR                vkGetPhysicalDeviceDisplayPlanePropertiesKHR;
		PFN_vkGetDisplayPlaneSupportedDisplaysKHR                       vkGetDisplayPlaneSupportedDisplaysKHR;
		PFN_vkGetDisplayModePropertiesKHR                               vkGetDisplayModePropertiesKHR;
		PFN_vkCreateDisplayModeKHR                                      vkCreateDisplayModeKHR;
		PFN_vkGetDisplayPlaneCapabilitiesKHR                            vkGetDisplayPlaneCapabilitiesKHR;
		PFN_vkCreateDisplayPlaneSurfaceKHR                              vkCreateDisplayPlaneSurfaceKHR;
		PFN_vkCreateDebugReportCallbackEXT                              vkCreateDebugReportCallbackEXT;
		PFN_vkDestroyDebugReportCallbackEXT                             vkDestroyDebugReportCallbackEXT;
		PFN_vkDebugReportMessageEXT                                     vkDebugReportMessageEXT;
		PFN_vkGetPhysicalDeviceExternalImageFormatPropertiesNV          vkGetPhysicalDeviceExternalImageFormatPropertiesNV;
		PFN_vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX           vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX;

#ifdef VK_USE_PLATFORM_WIN32_KHR
		PFN_vkCreateWin32SurfaceKHR                                     vkCreateWin32SurfaceKHR;
		PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR              vkGetPhysicalDeviceWin32PresentationSupportKHR;
#endif
#ifdef VK_USE_PLATFORM_XLIB_KHR
		PFN_vkCreateXlibSurfaceKHR                                      vkCreateXlibSurfaceKHR;
		PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR               vkGetPhysicalDeviceXlibPresentationSupportKHR;
#endif
#ifdef VK_USE_PLATFORM_XCB_KHR
		PFN_vkCreateXcbSurfaceKHR                                       vkCreateXcbSurfaceKHR;
		PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR                vkGetPhysicalDeviceXcbPresentationSupportKHR;
#endif
#ifdef VK_USE_PLATFORM_WAYLAND_KHR
		PFN_vkCreateWaylandSurfaceKHR                                   vkCreateWaylandSurfaceKHR;
		PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR            vkGetPhysicalDeviceWaylandPresentationSupportKHR;
#endif
#ifdef VK_USE_PLATFORM_MIR_KHR
		PFN_vkCreateMirSurfaceKHR                                       vkCreateMirSurfaceKHR;
		PFN_vkGetPhysicalDeviceMirPresentationSupportKHR                vkGetPhysicalDeviceMirPresentationSupportKHR;
#endif
#ifdef VK_USE_PLATFORM_ANDROID_KHR
		PFN_vkCreateAndroidSurfaceKHR                                   vkCreateAndroidSurfaceKHR;
#endif

		DEVA_FRAMEWORK_API VulkanInstanceFunctionSet();
		DEVA_FRAMEWORK_API VulkanInstanceFunctionSet(const VulkanInstanceFunctionSet &fset);
		DEVA_FRAMEWORK_API VulkanInstanceFunctionSet(VulkanInstanceFunctionSet &&fset);

		DEVA_FRAMEWORK_API VulkanInstanceFunctionSet& operator=(const VulkanInstanceFunctionSet &fset);
		DEVA_FRAMEWORK_API VulkanInstanceFunctionSet& operator=(VulkanInstanceFunctionSet &&fset);

		DEVA_FRAMEWORK_API ~VulkanInstanceFunctionSet();

	};
}

#endif //DEVA_FRAMEWORK_GRAPHICS_VULKAN_INSTANCE_FUNCTION_SET_HPP
