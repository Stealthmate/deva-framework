#include "InstanceFunctionSet.hpp"
#include "ImplDefaultVulkanInstanceFunctionSet.hpp"
#include "ImplDefaultVulkanDeviceFunctionSet.hpp"

using namespace DevaFramework;

#define LOAD(PFNNAME) \
VULKAN_LOG.println("Getting Instance PFN_" #PFNNAME "..."); \
vinstf.PFNNAME = (PFN_##PFNNAME) vkGetInstanceProcAddr(vkinstance, #PFNNAME); \
if(vinstf.PFNNAME == NULL) \
{ \
	VULKAN_WARN.println("Instance PFN_" #PFNNAME " not available (Extension not specified in VkInstanceCreateInfo?)"); \
	vinstf.PFNNAME = (PFN_##PFNNAME) internal::impldef_##PFNNAME; \
}

VulkanInstanceFunctionSet VulkanInstanceFunctionSet::load(VkInstance vkinstance)
{
	VulkanInstanceFunctionSet vinstf;
	LOAD(vkDestroyInstance);
	LOAD(vkEnumeratePhysicalDevices);
	LOAD(vkGetPhysicalDeviceFeatures);
	LOAD(vkGetPhysicalDeviceProperties);
	LOAD(vkGetPhysicalDeviceQueueFamilyProperties);
	LOAD(vkGetPhysicalDeviceSurfaceSupportKHR);
	LOAD(vkGetPhysicalDeviceSurfaceFormatsKHR);
	LOAD(vkGetPhysicalDeviceSurfaceCapabilitiesKHR);
	LOAD(vkGetPhysicalDeviceSurfacePresentModesKHR);
	LOAD(vkEnumerateDeviceExtensionProperties);
	LOAD(vkEnumerateDeviceLayerProperties);

	LOAD(vkCreateDevice);
	LOAD(vkDestroyDevice);
	LOAD(vkGetDeviceProcAddr);

#ifdef VK_USE_PLATFORM_WIN32_KHR
	LOAD(vkCreateWin32SurfaceKHR);
	LOAD(vkGetPhysicalDeviceWin32PresentationSupportKHR);
#endif //VK_USE_PLATFORM_WIN32_KHR

	LOAD(vkDestroySurfaceKHR);
	LOAD(vkCreateDebugReportCallbackEXT);

	return vinstf;
}

VulkanInstanceFunctionSet::VulkanInstanceFunctionSet() = default;
VulkanInstanceFunctionSet::VulkanInstanceFunctionSet(const VulkanInstanceFunctionSet &fset) = default;
VulkanInstanceFunctionSet::VulkanInstanceFunctionSet(VulkanInstanceFunctionSet &&fset) = default;

VulkanInstanceFunctionSet& VulkanInstanceFunctionSet::operator=(const VulkanInstanceFunctionSet &fset) = default;
VulkanInstanceFunctionSet& VulkanInstanceFunctionSet::operator=(VulkanInstanceFunctionSet &&fset) = default;

VulkanInstanceFunctionSet::~VulkanInstanceFunctionSet() = default;