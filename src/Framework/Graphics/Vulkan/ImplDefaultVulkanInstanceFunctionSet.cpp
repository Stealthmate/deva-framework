#include "ImplDefaultVulkanInstanceFunctionSet.hpp"

using namespace DevaFramework;

void DevaFramework::internal::impldef_vkDestroyInstance(VkInstance instance, const VkAllocationCallbacks *pAllocator) 
{
	VULKAN_ERR.println("Called vkDestroyInstance without proper driver PFN");
}

VkResult DevaFramework::internal::impldef_vkEnumeratePhysicalDevices(VkInstance instance, uint32_t* pPhysicalDeviceCount, VkPhysicalDevice* pPhysicalDevices)
{
	VULKAN_ERR.println("Called vkEnumeratePhysicalDevices without proper driver PFN");
	return VK_SUCCESS;
}
void DevaFramework::internal::impldef_vkGetPhysicalDeviceFeatures(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures* pFeatures)
{
	VULKAN_ERR.println("Called vkGetPhysicalDeviceFeatures without proper driver PFN");
}
void DevaFramework::internal::impldef_vkGetPhysicalDeviceProperties(VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties* pProperties)
{
	VULKAN_ERR.println("Called vkGetPhysicalDeviceProperties without proper driver PFN");
}
void DevaFramework::internal::impldef_vkGetPhysicalDeviceQueueFamilyProperties(VkPhysicalDevice physicalDevice, uint32_t* pQueueFamilyPropertyCount, VkQueueFamilyProperties* pQueueFamilyProperties)
{
	VULKAN_ERR.println("Called vkGetPhysicalDeviceQueueFamilyProperties without proper driver PFN");
}

VkResult DevaFramework::internal::impldef_vkCreateDevice(VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDevice* pDevice)
{
	VULKAN_ERR.println("Called vkCreateDevice without proper driver PFN");
	return VK_SUCCESS;
}

PFN_vkVoidFunction DevaFramework::internal::impldef_vkGetDeviceProcAddr(VkDevice device, const char* pName)
{
	VULKAN_ERR.println("Called vkGetDeviceProcAddr without proper driver PFN");
	return nullptr;
}

#ifdef DEVA_OS_WIN32

VkResult DevaFramework::internal::impldef_vkCreateWin32SurfaceKHR(VkInstance instance, const VkWin32SurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface)
{
	VULKAN_ERR.println("Called vkCreateWin32SurfaceKHR without proper driver PFN");
	return VK_SUCCESS;
}
VkBool32 DevaFramework::internal::impldef_vkGetPhysicalDeviceWin32PresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex)
{
	VULKAN_ERR.println("Called vkGetPhysicalDeviceWin32PresentationSupportKHR without proper driver PFN");
	return false;
}

#endif //DEVA_OS_WIN32

//KHR
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

void DevaFramework::internal::impldef_vkDestroySurfaceKHR(VkInstance instance, VkSurfaceKHR surface, const VkAllocationCallbacks* pAllocator)
{
	VULKAN_ERR.println("Called vkDestroySurfaceKHR without proper driver PFN");
}

VkResult DevaFramework::internal::impldef_vkCreateSwapchainKHR(VkDevice device, const VkSwapchainCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchain)
{
	VULKAN_ERR.println("Called vkCreateSwapchainKHR without proper driver PFN");
	return VK_SUCCESS;
}
VkResult DevaFramework::internal::impldef_vkGetSwapchainImagesKHR(VkDevice device, VkSwapchainKHR swapchain, uint32_t* pSwapchainImageCount, VkImage* pSwapchainImages)
{
	VULKAN_ERR.println("Called vkGetSwapchainImagesKHR without proper driver PFN");
	return VK_SUCCESS;
}
VkResult DevaFramework::internal::impldef_vkAcquireNextImageKHR(VkDevice device, VkSwapchainKHR swapchain, uint64_t timeout, VkSemaphore semaphore, VkFence fence, uint32_t* pImageIndex)
{
	VULKAN_ERR.println("Called vkAcquireNextImageKHR without proper driver PFN");
	return VK_SUCCESS;
}
VkResult DevaFramework::internal::impldef_vkQueuePresentKHR(VkQueue queue, const VkPresentInfoKHR* pPresentInfo)
{
	VULKAN_ERR.println("Called vkQueuePresentKHR without proper driver PFN");
	return VK_SUCCESS;
}
void DevaFramework::internal::impldef_vkDestroySwapchainKHR(VkDevice device, VkSwapchainKHR swapchain, const VkAllocationCallbacks* pAllocator)
{
	VULKAN_ERR.println("Called vkDestroySwapchainKHR without proper driver PFN");
}