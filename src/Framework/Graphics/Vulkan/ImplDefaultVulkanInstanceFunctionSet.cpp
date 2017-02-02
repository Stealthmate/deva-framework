#include "ImplDefaultVulkanInstanceFunctionSet.hpp"

using namespace DevaFramework;
void DevaFramework::internal::impldef_vkDestroyInstance(VkInstance instance, const VkAllocationCallbacks* pAllocator)
{
	VULKAN_ERR.println("Called vkDestroyInstance without proper driver PFN");
	return;
}
VkResult DevaFramework::internal::impldef_vkEnumeratePhysicalDevices(VkInstance instance, uint32_t* pPhysicalDeviceCount, VkPhysicalDevice* pPhysicalDevices)
{
	VULKAN_ERR.println("Called vkEnumeratePhysicalDevices without proper driver PFN");
	return VK_SUCCESS;
}
void DevaFramework::internal::impldef_vkGetPhysicalDeviceFeatures(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures* pFeatures)
{
	VULKAN_ERR.println("Called vkGetPhysicalDeviceFeatures without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkGetPhysicalDeviceFormatProperties(VkPhysicalDevice physicalDevice, VkFormat format, VkFormatProperties* pFormatProperties)
{
	VULKAN_ERR.println("Called vkGetPhysicalDeviceFormatProperties without proper driver PFN");
	return;
}
VkResult DevaFramework::internal::impldef_vkGetPhysicalDeviceImageFormatProperties(VkPhysicalDevice physicalDevice, VkFormat format, VkImageType type, VkImageTiling tiling, VkImageUsageFlags usage, VkImageCreateFlags flags, VkImageFormatProperties* pImageFormatProperties)
{
	VULKAN_ERR.println("Called vkGetPhysicalDeviceImageFormatProperties without proper driver PFN");
	return VK_SUCCESS;
}
void DevaFramework::internal::impldef_vkGetPhysicalDeviceProperties(VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties* pProperties)
{
	VULKAN_ERR.println("Called vkGetPhysicalDeviceProperties without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkGetPhysicalDeviceQueueFamilyProperties(VkPhysicalDevice physicalDevice, uint32_t* pQueueFamilyPropertyCount, VkQueueFamilyProperties* pQueueFamilyProperties)
{
	VULKAN_ERR.println("Called vkGetPhysicalDeviceQueueFamilyProperties without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkGetPhysicalDeviceMemoryProperties(VkPhysicalDevice physicalDevice, VkPhysicalDeviceMemoryProperties* pMemoryProperties)
{
	VULKAN_ERR.println("Called vkGetPhysicalDeviceMemoryProperties without proper driver PFN");
	return;
}
PFN_vkVoidFunction DevaFramework::internal::impldef_vkGetInstanceProcAddr(VkInstance instance, const char* pName)
{
	VULKAN_ERR.println("Called vkGetInstanceProcAddr without proper driver PFN");
	return nullptr;
}
VkResult DevaFramework::internal::impldef_vkCreateDevice(VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDevice* pDevice)
{
	VULKAN_ERR.println("Called vkCreateDevice without proper driver PFN");
	return VK_SUCCESS;
}
VkResult DevaFramework::internal::impldef_vkEnumerateDeviceExtensionProperties(VkPhysicalDevice physicalDevice, const char* pLayerName, uint32_t* pPropertyCount, VkExtensionProperties* pProperties)
{
	VULKAN_ERR.println("Called vkEnumerateDeviceExtensionProperties without proper driver PFN");
	return VK_SUCCESS;
}
VkResult DevaFramework::internal::impldef_vkEnumerateDeviceLayerProperties(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkLayerProperties* pProperties)
{
	VULKAN_ERR.println("Called vkEnumerateDeviceLayerProperties without proper driver PFN");
	return VK_SUCCESS;
}
void DevaFramework::internal::impldef_vkGetPhysicalDeviceSparseImageFormatProperties(VkPhysicalDevice physicalDevice, VkFormat format, VkImageType type, VkSampleCountFlagBits samples, VkImageUsageFlags usage, VkImageTiling tiling, uint32_t* pPropertyCount, VkSparseImageFormatProperties* pProperties)
{
	VULKAN_ERR.println("Called vkGetPhysicalDeviceSparseImageFormatProperties without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkDestroySurfaceKHR(VkInstance instance, VkSurfaceKHR surface, const VkAllocationCallbacks* pAllocator)
{
	VULKAN_ERR.println("Called vkDestroySurfaceKHR without proper driver PFN");
	return;
}
VkResult DevaFramework::internal::impldef_vkGetPhysicalDeviceSurfaceSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, VkSurfaceKHR surface, VkBool32* pSupported)
{
	VULKAN_ERR.println("Called vkGetPhysicalDeviceSurfaceSupportKHR without proper driver PFN");
	return VK_SUCCESS;
}
VkResult DevaFramework::internal::impldef_vkGetPhysicalDeviceSurfaceCapabilitiesKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, VkSurfaceCapabilitiesKHR* pSurfaceCapabilities)
{
	VULKAN_ERR.println("Called vkGetPhysicalDeviceSurfaceCapabilitiesKHR without proper driver PFN");
	return VK_SUCCESS;
}
VkResult DevaFramework::internal::impldef_vkGetPhysicalDeviceSurfaceFormatsKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, uint32_t* pSurfaceFormatCount, VkSurfaceFormatKHR* pSurfaceFormats)
{
	VULKAN_ERR.println("Called vkGetPhysicalDeviceSurfaceFormatsKHR without proper driver PFN");
	return VK_SUCCESS;
}
VkResult DevaFramework::internal::impldef_vkGetPhysicalDeviceSurfacePresentModesKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, uint32_t* pPresentModeCount, VkPresentModeKHR* pPresentModes)
{
	VULKAN_ERR.println("Called vkGetPhysicalDeviceSurfacePresentModesKHR without proper driver PFN");
	return VK_SUCCESS;
}
VkResult DevaFramework::internal::impldef_vkGetPhysicalDeviceDisplayPropertiesKHR(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkDisplayPropertiesKHR* pProperties)
{
	VULKAN_ERR.println("Called vkGetPhysicalDeviceDisplayPropertiesKHR without proper driver PFN");
	return VK_SUCCESS;
}
VkResult DevaFramework::internal::impldef_vkGetPhysicalDeviceDisplayPlanePropertiesKHR(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkDisplayPlanePropertiesKHR* pProperties)
{
	VULKAN_ERR.println("Called vkGetPhysicalDeviceDisplayPlanePropertiesKHR without proper driver PFN");
	return VK_SUCCESS;
}
VkResult DevaFramework::internal::impldef_vkGetDisplayPlaneSupportedDisplaysKHR(VkPhysicalDevice physicalDevice, uint32_t planeIndex, uint32_t* pDisplayCount, VkDisplayKHR* pDisplays)
{
	VULKAN_ERR.println("Called vkGetDisplayPlaneSupportedDisplaysKHR without proper driver PFN");
	return VK_SUCCESS;
}
VkResult DevaFramework::internal::impldef_vkGetDisplayModePropertiesKHR(VkPhysicalDevice physicalDevice, VkDisplayKHR display, uint32_t* pPropertyCount, VkDisplayModePropertiesKHR* pProperties)
{
	VULKAN_ERR.println("Called vkGetDisplayModePropertiesKHR without proper driver PFN");
	return VK_SUCCESS;
}
VkResult DevaFramework::internal::impldef_vkCreateDisplayModeKHR(VkPhysicalDevice physicalDevice, VkDisplayKHR display, const VkDisplayModeCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDisplayModeKHR* pMode)
{
	VULKAN_ERR.println("Called vkCreateDisplayModeKHR without proper driver PFN");
	return VK_SUCCESS;
}
VkResult DevaFramework::internal::impldef_vkGetDisplayPlaneCapabilitiesKHR(VkPhysicalDevice physicalDevice, VkDisplayModeKHR mode, uint32_t planeIndex, VkDisplayPlaneCapabilitiesKHR* pCapabilities)
{
	VULKAN_ERR.println("Called vkGetDisplayPlaneCapabilitiesKHR without proper driver PFN");
	return VK_SUCCESS;
}
VkResult DevaFramework::internal::impldef_vkCreateDisplayPlaneSurfaceKHR(VkInstance instance, const VkDisplaySurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface)
{
	VULKAN_ERR.println("Called vkCreateDisplayPlaneSurfaceKHR without proper driver PFN");
	return VK_SUCCESS;
}
#ifdef VK_USE_PLATFORM_XLIB_KHR
VkResult DevaFramework::internal::impldef_vkCreateXlibSurfaceKHR(VkInstance instance, const VkXlibSurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface)
{
	VULKAN_ERR.println("Called vkCreateXlibSurfaceKHR without proper driver PFN");
	return VK_SUCCESS;
}
VkBool32 DevaFramework::internal::impldef_vkGetPhysicalDeviceXlibPresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, Display* dpy, VisualID visualID)
{
	VULKAN_ERR.println("Called vkGetPhysicalDeviceXlibPresentationSupportKHR without proper driver PFN");
	return VK_TRUE;
}
#endif
#ifdef VK_USE_PLATFORM_XCB_KHR
VkResult DevaFramework::internal::impldef_vkCreateXcbSurfaceKHR(VkInstance instance, const VkXcbSurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface)
{
	VULKAN_ERR.println("Called vkCreateXcbSurfaceKHR without proper driver PFN");
	return VK_SUCCESS;
}
VkBool32 DevaFramework::internal::impldef_vkGetPhysicalDeviceXcbPresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, xcb_connection_t* connection, xcb_visualid_t visual_id)
{
	VULKAN_ERR.println("Called vkGetPhysicalDeviceXcbPresentationSupportKHR without proper driver PFN");
	return VK_TRUE;
}
#endif
#ifdef VK_USE_PLATFORM_WAYLAND_KHR
VkResult DevaFramework::internal::impldef_vkCreateWaylandSurfaceKHR(VkInstance instance, const VkWaylandSurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface)
{
	VULKAN_ERR.println("Called vkCreateWaylandSurfaceKHR without proper driver PFN");
	return VK_SUCCESS;
}
VkBool32 DevaFramework::internal::impldef_vkGetPhysicalDeviceWaylandPresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, struct wl_display* display)
{
	VULKAN_ERR.println("Called vkGetPhysicalDeviceWaylandPresentationSupportKHR without proper driver PFN");
	return VK_TRUE;
}
#endif
#ifdef VK_USE_PLATFORM_MIR_KHR
VkResult DevaFramework::internal::impldef_vkCreateMirSurfaceKHR(VkInstance instance, const VkMirSurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface)
{
	VULKAN_ERR.println("Called vkCreateMirSurfaceKHR without proper driver PFN");
	return VK_SUCCESS;
}
VkBool32 DevaFramework::internal::impldef_vkGetPhysicalDeviceMirPresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, MirConnection* connection)
{
	VULKAN_ERR.println("Called vkGetPhysicalDeviceMirPresentationSupportKHR without proper driver PFN");
	return VK_TRUE;
}
#endif
#ifdef VK_USE_PLATFORM_ANDROID_KHR
VkResult DevaFramework::internal::impldef_vkCreateAndroidSurfaceKHR(VkInstance instance, const VkAndroidSurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface)
{
	VULKAN_ERR.println("Called vkCreateAndroidSurfaceKHR without proper driver PFN");
	return VK_SUCCESS;
}
#endif
#ifdef VK_USE_PLATFORM_WIN32_KHR
VkResult DevaFramework::internal::impldef_vkCreateWin32SurfaceKHR(VkInstance instance, const VkWin32SurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface)
{
	VULKAN_ERR.println("Called vkCreateWin32SurfaceKHR without proper driver PFN");
	return VK_SUCCESS;
}
VkBool32 DevaFramework::internal::impldef_vkGetPhysicalDeviceWin32PresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex)
{
	VULKAN_ERR.println("Called vkGetPhysicalDeviceWin32PresentationSupportKHR without proper driver PFN");
	return VK_TRUE;
}
#endif
VkResult DevaFramework::internal::impldef_vkCreateDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback)
{
	VULKAN_ERR.println("Called vkCreateDebugReportCallbackEXT without proper driver PFN");
	return VK_SUCCESS;
}
void DevaFramework::internal::impldef_vkDestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator)
{
	VULKAN_ERR.println("Called vkDestroyDebugReportCallbackEXT without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkDebugReportMessageEXT(VkInstance instance, VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType, uint64_t object, size_t location, int32_t messageCode, const char* pLayerPrefix, const char* pMessage)
{
	VULKAN_ERR.println("Called vkDebugReportMessageEXT without proper driver PFN");
	return;
}
VkResult DevaFramework::internal::impldef_vkGetPhysicalDeviceExternalImageFormatPropertiesNV(VkPhysicalDevice physicalDevice, VkFormat format, VkImageType type, VkImageTiling tiling, VkImageUsageFlags usage, VkImageCreateFlags flags, VkExternalMemoryHandleTypeFlagsNV externalHandleType, VkExternalImageFormatPropertiesNV* pExternalImageFormatProperties)
{
	VULKAN_ERR.println("Called vkGetPhysicalDeviceExternalImageFormatPropertiesNV without proper driver PFN");
	return VK_SUCCESS;
}
void DevaFramework::internal::impldef_vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX(VkPhysicalDevice physicalDevice, VkDeviceGeneratedCommandsFeaturesNVX* pFeatures, VkDeviceGeneratedCommandsLimitsNVX* pLimits)
{
	VULKAN_ERR.println("Called vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX without proper driver PFN");
	return;
}
