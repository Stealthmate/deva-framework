#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_IMPL_DEFAULT_VULKAN_INSTANCE_FUNCTION_SET_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_IMPL_DEFAULT_VULKAN_INSTANCE_FUNCTION_SET_HPP

#include "Config.hpp"

namespace DevaFramework
{
	namespace internal
	{
		void impldef_vkDestroyInstance(VkInstance instance, const VkAllocationCallbacks *pAllocator);
		VkResult impldef_vkEnumeratePhysicalDevices(VkInstance instance, uint32_t* pPhysicalDeviceCount, VkPhysicalDevice* pPhysicalDevices);
		void impldef_vkGetPhysicalDeviceFeatures(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures* pFeatures);
		void impldef_vkGetPhysicalDeviceProperties(VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties* pProperties);
		void impldef_vkGetPhysicalDeviceQueueFamilyProperties(VkPhysicalDevice physicalDevice, uint32_t* pQueueFamilyPropertyCount, VkQueueFamilyProperties* pQueueFamilyProperties);
		VkResult impldef_vkEnumerateDeviceExtensionProperties(VkPhysicalDevice physicalDevice, const char* pLayerName, uint32_t* pPropertyCount, VkExtensionProperties* pProperties);
		VkResult impldef_vkEnumerateDeviceLayerProperties(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkLayerProperties* pProperties);

		VkResult impldef_vkCreateDevice(VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDevice* pDevice);

		PFN_vkVoidFunction impldef_vkGetDeviceProcAddr(VkDevice device, const char* pName);

#ifdef DEVA_OS_WIN32

		VkResult impldef_vkCreateWin32SurfaceKHR(VkInstance instance, const VkWin32SurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
		VkBool32 impldef_vkGetPhysicalDeviceWin32PresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex);

#endif //DEVA_OS_WIN32

		//KHR
		VkResult impldef_vkGetPhysicalDeviceSurfaceSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, VkSurfaceKHR surface, VkBool32* pSupported);
		VkResult impldef_vkGetPhysicalDeviceSurfaceCapabilitiesKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, VkSurfaceCapabilitiesKHR* pSurfaceCapabilities);
		VkResult impldef_vkGetPhysicalDeviceSurfaceFormatsKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, uint32_t* pSurfaceFormatCount, VkSurfaceFormatKHR* pSurfaceFormats);
		VkResult impldef_vkGetPhysicalDeviceSurfacePresentModesKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, uint32_t* pPresentModeCount, VkPresentModeKHR* pPresentModes);

		void impldef_vkDestroySurfaceKHR(VkInstance instance, VkSurfaceKHR surface, const VkAllocationCallbacks* pAllocator);

		VkResult impldef_vkCreateDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback);
	}
}


#endif //DEVA_FRAMEWORK_GRAPHICS_VULKAN_IMPL_DEFAULT_VULKAN_INSTANCE_FUNCTION_SET_HPP