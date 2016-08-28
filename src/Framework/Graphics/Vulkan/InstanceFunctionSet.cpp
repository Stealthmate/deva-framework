#include "InstanceFunctionSet.hpp"
#include "ImplDefaultVulkanInstanceFunctionSet.hpp"
#include "ImplDefaultVulkanDeviceFunctionSet.hpp"

using namespace DevaFramework;

#define LOAD(PFNNAME) \
VULKAN_LOG.println("Getting Instance PFN_" #PFNNAME "..."); \
this->PFNNAME = (PFN_##PFNNAME) vkGetInstanceProcAddr(vkinstance, #PFNNAME); \
if(this->PFNNAME == NULL) \
{ \
	VULKAN_WARN.println("Instance PFN_" #PFNNAME " not available (Extension not specified in VkInstanceCreateInfo?)"); \
	this->PFNNAME = (PFN_##PFNNAME) internal::impldef_##PFNNAME; \
}

void InstanceFunctionSet::load(VkInstance vkinstance)
{
	LOAD(vkDestroyInstance);
	LOAD(vkEnumeratePhysicalDevices);
	LOAD(vkGetPhysicalDeviceFeatures);
	LOAD(vkGetPhysicalDeviceProperties);
	LOAD(vkGetPhysicalDeviceQueueFamilyProperties);
	LOAD(vkGetPhysicalDeviceSurfaceSupportKHR);

	LOAD(vkCreateDevice);
	LOAD(vkDestroyDevice);
	LOAD(vkGetDeviceProcAddr);

#ifdef VK_USE_PLATFORM_WIN32_KHR
	LOAD(vkCreateWin32SurfaceKHR);
	LOAD(vkGetPhysicalDeviceWin32PresentationSupportKHR);
#endif //VK_USE_PLATFORM_WIN32_KHR

	LOAD(vkDestroySurfaceKHR);
	LOAD(vkAcquireNextImageKHR);
}

InstanceFunctionSet::InstanceFunctionSet() = default;
InstanceFunctionSet::InstanceFunctionSet(const InstanceFunctionSet &fset) = default;
InstanceFunctionSet::InstanceFunctionSet(InstanceFunctionSet &&fset) = default;

InstanceFunctionSet& InstanceFunctionSet::operator=(const InstanceFunctionSet &fset) = default;
InstanceFunctionSet& InstanceFunctionSet::operator=(InstanceFunctionSet &&fset) = default;

InstanceFunctionSet::~InstanceFunctionSet() = default;