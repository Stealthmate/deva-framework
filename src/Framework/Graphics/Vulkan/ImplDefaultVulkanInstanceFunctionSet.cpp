#include "ImplDefaultVulkanInstanceFunctionSet.hpp"

using namespace DevaFramework;
void DevaFramework::internal::impldef_vkDestroyInstance(VkInstance instance, const VkAllocationCallbacks* pAllocator)
{
	LOG_VULKAN.e("Called vkDestroyInstance without proper driver PFN");
	return;
}
VkResult DevaFramework::internal::impldef_vkEnumeratePhysicalDevices(VkInstance instance, uint32_t* pPhysicalDeviceCount, VkPhysicalDevice* pPhysicalDevices)
{
	LOG_VULKAN.e("Called vkEnumeratePhysicalDevices without proper driver PFN");
	return VK_SUCCESS;
}
void DevaFramework::internal::impldef_vkGetPhysicalDeviceFeatures(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures* pFeatures)
{
	LOG_VULKAN.e("Called vkGetPhysicalDeviceFeatures without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkGetPhysicalDeviceFormatProperties(VkPhysicalDevice physicalDevice, VkFormat format, VkFormatProperties* pFormatProperties)
{
	LOG_VULKAN.e("Called vkGetPhysicalDeviceFormatProperties without proper driver PFN");
	return;
}
VkResult DevaFramework::internal::impldef_vkGetPhysicalDeviceImageFormatProperties(VkPhysicalDevice physicalDevice, VkFormat format, VkImageType type, VkImageTiling tiling, VkImageUsageFlags usage, VkImageCreateFlags flags, VkImageFormatProperties* pImageFormatProperties)
{
	LOG_VULKAN.e("Called vkGetPhysicalDeviceImageFormatProperties without proper driver PFN");
	return VK_SUCCESS;
}
void DevaFramework::internal::impldef_vkGetPhysicalDeviceProperties(VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties* pProperties)
{
	LOG_VULKAN.e("Called vkGetPhysicalDeviceProperties without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkGetPhysicalDeviceQueueFamilyProperties(VkPhysicalDevice physicalDevice, uint32_t* pQueueFamilyPropertyCount, VkQueueFamilyProperties* pQueueFamilyProperties)
{
	LOG_VULKAN.e("Called vkGetPhysicalDeviceQueueFamilyProperties without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkGetPhysicalDeviceMemoryProperties(VkPhysicalDevice physicalDevice, VkPhysicalDeviceMemoryProperties* pMemoryProperties)
{
	LOG_VULKAN.e("Called vkGetPhysicalDeviceMemoryProperties without proper driver PFN");
	return;
}
PFN_vkVoidFunction DevaFramework::internal::impldef_vkGetInstanceProcAddr(VkInstance instance, const char* pName)
{
	LOG_VULKAN.e("Called vkGetInstanceProcAddr without proper driver PFN");
	return nullptr;
}
VkResult DevaFramework::internal::impldef_vkCreateDevice(VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDevice* pDevice)
{
	LOG_VULKAN.e("Called vkCreateDevice without proper driver PFN");
	return VK_SUCCESS;
}
VkResult DevaFramework::internal::impldef_vkEnumerateDeviceExtensionProperties(VkPhysicalDevice physicalDevice, const char* pLayerName, uint32_t* pPropertyCount, VkExtensionProperties* pProperties)
{
	LOG_VULKAN.e("Called vkEnumerateDeviceExtensionProperties without proper driver PFN");
	return VK_SUCCESS;
}
VkResult DevaFramework::internal::impldef_vkEnumerateDeviceLayerProperties(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkLayerProperties* pProperties)
{
	LOG_VULKAN.e("Called vkEnumerateDeviceLayerProperties without proper driver PFN");
	return VK_SUCCESS;
}
void DevaFramework::internal::impldef_vkGetPhysicalDeviceSparseImageFormatProperties(VkPhysicalDevice physicalDevice, VkFormat format, VkImageType type, VkSampleCountFlagBits samples, VkImageUsageFlags usage, VkImageTiling tiling, uint32_t* pPropertyCount, VkSparseImageFormatProperties* pProperties)
{
	LOG_VULKAN.e("Called vkGetPhysicalDeviceSparseImageFormatProperties without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkDestroySurfaceKHR(VkInstance instance, VkSurfaceKHR surface, const VkAllocationCallbacks* pAllocator)
{
	LOG_VULKAN.e("Called vkDestroySurfaceKHR without proper driver PFN");
	return;
}
VkResult DevaFramework::internal::impldef_vkGetPhysicalDeviceSurfaceSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, VkSurfaceKHR surface, VkBool32* pSupported)
{
	LOG_VULKAN.e("Called vkGetPhysicalDeviceSurfaceSupportKHR without proper driver PFN");
	return VK_SUCCESS;
}
VkResult DevaFramework::internal::impldef_vkGetPhysicalDeviceSurfaceCapabilitiesKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, VkSurfaceCapabilitiesKHR* pSurfaceCapabilities)
{
	LOG_VULKAN.e("Called vkGetPhysicalDeviceSurfaceCapabilitiesKHR without proper driver PFN");
	return VK_SUCCESS;
}
VkResult DevaFramework::internal::impldef_vkGetPhysicalDeviceSurfaceFormatsKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, uint32_t* pSurfaceFormatCount, VkSurfaceFormatKHR* pSurfaceFormats)
{
	LOG_VULKAN.e("Called vkGetPhysicalDeviceSurfaceFormatsKHR without proper driver PFN");
	return VK_SUCCESS;
}
VkResult DevaFramework::internal::impldef_vkGetPhysicalDeviceSurfacePresentModesKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, uint32_t* pPresentModeCount, VkPresentModeKHR* pPresentModes)
{
	LOG_VULKAN.e("Called vkGetPhysicalDeviceSurfacePresentModesKHR without proper driver PFN");
	return VK_SUCCESS;
}
VkResult DevaFramework::internal::impldef_vkGetPhysicalDeviceDisplayPropertiesKHR(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkDisplayPropertiesKHR* pProperties)
{
	LOG_VULKAN.e("Called vkGetPhysicalDeviceDisplayPropertiesKHR without proper driver PFN");
	return VK_SUCCESS;
}
VkResult DevaFramework::internal::impldef_vkGetPhysicalDeviceDisplayPlanePropertiesKHR(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkDisplayPlanePropertiesKHR* pProperties)
{
	LOG_VULKAN.e("Called vkGetPhysicalDeviceDisplayPlanePropertiesKHR without proper driver PFN");
	return VK_SUCCESS;
}
VkResult DevaFramework::internal::impldef_vkGetDisplayPlaneSupportedDisplaysKHR(VkPhysicalDevice physicalDevice, uint32_t planeIndex, uint32_t* pDisplayCount, VkDisplayKHR* pDisplays)
{
	LOG_VULKAN.e("Called vkGetDisplayPlaneSupportedDisplaysKHR without proper driver PFN");
	return VK_SUCCESS;
}
VkResult DevaFramework::internal::impldef_vkGetDisplayModePropertiesKHR(VkPhysicalDevice physicalDevice, VkDisplayKHR display, uint32_t* pPropertyCount, VkDisplayModePropertiesKHR* pProperties)
{
	LOG_VULKAN.e("Called vkGetDisplayModePropertiesKHR without proper driver PFN");
	return VK_SUCCESS;
}
VkResult DevaFramework::internal::impldef_vkCreateDisplayModeKHR(VkPhysicalDevice physicalDevice, VkDisplayKHR display, const VkDisplayModeCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDisplayModeKHR* pMode)
{
	LOG_VULKAN.e("Called vkCreateDisplayModeKHR without proper driver PFN");
	return VK_SUCCESS;
}
VkResult DevaFramework::internal::impldef_vkGetDisplayPlaneCapabilitiesKHR(VkPhysicalDevice physicalDevice, VkDisplayModeKHR mode, uint32_t planeIndex, VkDisplayPlaneCapabilitiesKHR* pCapabilities)
{
	LOG_VULKAN.e("Called vkGetDisplayPlaneCapabilitiesKHR without proper driver PFN");
	return VK_SUCCESS;
}
VkResult DevaFramework::internal::impldef_vkCreateDisplayPlaneSurfaceKHR(VkInstance instance, const VkDisplaySurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface)
{
	LOG_VULKAN.e("Called vkCreateDisplayPlaneSurfaceKHR without proper driver PFN");
	return VK_SUCCESS;
}
#ifdef VK_USE_PLATFORM_XLIB_KHR
VkResult DevaFramework::internal::impldef_vkCreateXlibSurfaceKHR(VkInstance instance, const VkXlibSurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface)
{
	LOG_VULKAN.e("Called vkCreateXlibSurfaceKHR without proper driver PFN");
	return VK_SUCCESS;
}
VkBool32 DevaFramework::internal::impldef_vkGetPhysicalDeviceXlibPresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, Display* dpy, VisualID visualID)
{
	LOG_VULKAN.e("Called vkGetPhysicalDeviceXlibPresentationSupportKHR without proper driver PFN");
	return VK_TRUE;
}
#endif
#ifdef VK_USE_PLATFORM_XCB_KHR
VkResult DevaFramework::internal::impldef_vkCreateXcbSurfaceKHR(VkInstance instance, const VkXcbSurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface)
{
	LOG_VULKAN.e("Called vkCreateXcbSurfaceKHR without proper driver PFN");
	return VK_SUCCESS;
}
VkBool32 DevaFramework::internal::impldef_vkGetPhysicalDeviceXcbPresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, xcb_connection_t* connection, xcb_visualid_t visual_id)
{
	LOG_VULKAN.e("Called vkGetPhysicalDeviceXcbPresentationSupportKHR without proper driver PFN");
	return VK_TRUE;
}
#endif
#ifdef VK_USE_PLATFORM_WAYLAND_KHR
VkResult DevaFramework::internal::impldef_vkCreateWaylandSurfaceKHR(VkInstance instance, const VkWaylandSurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface)
{
	LOG_VULKAN.e("Called vkCreateWaylandSurfaceKHR without proper driver PFN");
	return VK_SUCCESS;
}
VkBool32 DevaFramework::internal::impldef_vkGetPhysicalDeviceWaylandPresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, struct wl_display* display)
{
	LOG_VULKAN.e("Called vkGetPhysicalDeviceWaylandPresentationSupportKHR without proper driver PFN");
	return VK_TRUE;
}
#endif
#ifdef VK_USE_PLATFORM_MIR_KHR
VkResult DevaFramework::internal::impldef_vkCreateMirSurfaceKHR(VkInstance instance, const VkMirSurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface)
{
	LOG_VULKAN.e("Called vkCreateMirSurfaceKHR without proper driver PFN");
	return VK_SUCCESS;
}
VkBool32 DevaFramework::internal::impldef_vkGetPhysicalDeviceMirPresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, MirConnection* connection)
{
	LOG_VULKAN.e("Called vkGetPhysicalDeviceMirPresentationSupportKHR without proper driver PFN");
	return VK_TRUE;
}
#endif
#ifdef VK_USE_PLATFORM_ANDROID_KHR
VkResult DevaFramework::internal::impldef_vkCreateAndroidSurfaceKHR(VkInstance instance, const VkAndroidSurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface)
{
	LOG_VULKAN.e("Called vkCreateAndroidSurfaceKHR without proper driver PFN");
	return VK_SUCCESS;
}
#endif
#ifdef VK_USE_PLATFORM_WIN32_KHR
VkResult DevaFramework::internal::impldef_vkCreateWin32SurfaceKHR(VkInstance instance, const VkWin32SurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface)
{
	LOG_VULKAN.e("Called vkCreateWin32SurfaceKHR without proper driver PFN");
	return VK_SUCCESS;
}
VkBool32 DevaFramework::internal::impldef_vkGetPhysicalDeviceWin32PresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex)
{
	LOG_VULKAN.e("Called vkGetPhysicalDeviceWin32PresentationSupportKHR without proper driver PFN");
	return VK_TRUE;
}
#endif
VkResult DevaFramework::internal::impldef_vkCreateDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback)
{
	LOG_VULKAN.e("Called vkCreateDebugReportCallbackEXT without proper driver PFN");
	return VK_SUCCESS;
}
void DevaFramework::internal::impldef_vkDestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator)
{
	LOG_VULKAN.e("Called vkDestroyDebugReportCallbackEXT without proper driver PFN");
	return;
}
void DevaFramework::internal::impldef_vkDebugReportMessageEXT(VkInstance instance, VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType, uint64_t object, size_t location, int32_t messageCode, const char* pLayerPrefix, const char* pMessage)
{
	LOG_VULKAN.e("Called vkDebugReportMessageEXT without proper driver PFN");
	return;
}
VkResult DevaFramework::internal::impldef_vkGetPhysicalDeviceExternalImageFormatPropertiesNV(VkPhysicalDevice physicalDevice, VkFormat format, VkImageType type, VkImageTiling tiling, VkImageUsageFlags usage, VkImageCreateFlags flags, VkExternalMemoryHandleTypeFlagsNV externalHandleType, VkExternalImageFormatPropertiesNV* pExternalImageFormatProperties)
{
	LOG_VULKAN.e("Called vkGetPhysicalDeviceExternalImageFormatPropertiesNV without proper driver PFN");
	return VK_SUCCESS;
}
void DevaFramework::internal::impldef_vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX(VkPhysicalDevice physicalDevice, VkDeviceGeneratedCommandsFeaturesNVX* pFeatures, VkDeviceGeneratedCommandsLimitsNVX* pLimits)
{
	LOG_VULKAN.e("Called vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX without proper driver PFN");
	return;
}
