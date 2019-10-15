#include "VulkanInstanceFunctionSet.hpp"
#include "ImplDefaultVulkanInstanceFunctionSet.hpp"
#include "ImplDefaultVulkanDeviceFunctionSet.hpp"

using namespace DevaFramework;
using Vulkan::LOG_VULKAN;

#define LOAD(PFNNAME) \
LOG_VULKAN.v("Getting Instance PFN_" #PFNNAME "..."); \
vinstf.PFNNAME = (PFN_##PFNNAME) internal::vkGetInstanceProcAddr(vkinstance, #PFNNAME); \
if(vinstf.PFNNAME == NULL) \
{ \
	LOG_VULKAN.v("Instance PFN_" #PFNNAME " not available. Assigning default implementation (throw exception)"); \
	vinstf.PFNNAME = (PFN_##PFNNAME) internal::impldef_##PFNNAME; \
}

VulkanInstanceFunctionSet VulkanInstanceFunctionSet::load(VkInstance vkinstance)
{
	VulkanInstanceFunctionSet vinstf;

	LOAD(vkGetDeviceProcAddr);
	LOAD(vkDestroyInstance);
	LOAD(vkEnumeratePhysicalDevices);
	LOAD(vkGetPhysicalDeviceFeatures);
	LOAD(vkGetPhysicalDeviceFormatProperties);
	LOAD(vkGetPhysicalDeviceImageFormatProperties);
	LOAD(vkGetPhysicalDeviceProperties);
	LOAD(vkGetPhysicalDeviceQueueFamilyProperties);
	LOAD(vkGetPhysicalDeviceMemoryProperties);
	LOAD(vkCreateDevice);
	LOAD(vkEnumerateDeviceExtensionProperties);
	LOAD(vkEnumerateDeviceLayerProperties);
	LOAD(vkGetPhysicalDeviceSparseImageFormatProperties);
	LOAD(vkDestroySurfaceKHR);
	LOAD(vkGetPhysicalDeviceSurfaceSupportKHR);
	LOAD(vkGetPhysicalDeviceSurfaceCapabilitiesKHR);
	LOAD(vkGetPhysicalDeviceSurfaceFormatsKHR);
	LOAD(vkGetPhysicalDeviceSurfacePresentModesKHR);
	LOAD(vkGetPhysicalDeviceDisplayPropertiesKHR);
	LOAD(vkGetPhysicalDeviceDisplayPlanePropertiesKHR);
	LOAD(vkGetDisplayPlaneSupportedDisplaysKHR);
	LOAD(vkGetDisplayModePropertiesKHR);
	LOAD(vkCreateDisplayModeKHR);
	LOAD(vkGetDisplayPlaneCapabilitiesKHR);
	LOAD(vkCreateDisplayPlaneSurfaceKHR);
	LOAD(vkCreateDebugReportCallbackEXT);
	LOAD(vkDestroyDebugReportCallbackEXT);
	LOAD(vkDebugReportMessageEXT);
	LOAD(vkGetPhysicalDeviceExternalImageFormatPropertiesNV);
	LOAD(vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX);

#ifdef VK_USE_PLATFORM_WIN32_KHR
	LOAD(vkCreateWin32SurfaceKHR);
	LOAD(vkGetPhysicalDeviceWin32PresentationSupportKHR);
#endif
#ifdef VK_USE_PLATFORM_XLIB_KHR
	LOAD(vkCreateXlibSurfaceKHR);
	LOAD(vkGetPhysicalDeviceXlibPresentationSupportKHR);
#endif
#ifdef VK_USE_PLATFORM_XCB_KHR
	LOAD(vkCreateXcbSurfaceKHR);
	LOAD(vkGetPhysicalDeviceXcbPresentationSupportKHR);
#endif
#ifdef VK_USE_PLATFORM_WAYLAND_KHR
	LOAD(vkCreateWaylandSurfaceKHR);
	LOAD(vkGetPhysicalDeviceWaylandPresentationSupportKHR);
#endif
#ifdef VK_USE_PLATFORM_MIR_KHR
	LOAD(vkCreateMirSurfaceKHR);
	LOAD(vkGetPhysicalDeviceMirPresentationSupportKHR);
#endif
#ifdef VK_USE_PLATFORM_ANDROID_KHR
	LOAD(vkCreateAndroidSurfaceKHR);
#endif

	return vinstf;
}

VulkanInstanceFunctionSet::VulkanInstanceFunctionSet() = default;
VulkanInstanceFunctionSet::VulkanInstanceFunctionSet(const VulkanInstanceFunctionSet &fset) = default;
VulkanInstanceFunctionSet::VulkanInstanceFunctionSet(VulkanInstanceFunctionSet &&fset) = default;

VulkanInstanceFunctionSet& VulkanInstanceFunctionSet::operator=(const VulkanInstanceFunctionSet &fset) = default;
VulkanInstanceFunctionSet& VulkanInstanceFunctionSet::operator=(VulkanInstanceFunctionSet &&fset) = default;

VulkanInstanceFunctionSet::~VulkanInstanceFunctionSet() = default;