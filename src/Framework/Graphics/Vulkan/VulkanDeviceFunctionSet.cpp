#include "VulkanDeviceFunctionSet.hpp"
#include "ImplDefaultVulkanDeviceFunctionSet.hpp"

using namespace DevaFramework;

#define LOAD(PFNNAME) \
VULKAN_LOG.println("Getting Device PFN_" #PFNNAME "..."); \
this->PFNNAME = (PFN_##PFNNAME) vkinstance.getFunctionSet().vkGetDeviceProcAddr(vkdevice, #PFNNAME); \
if(this->PFNNAME == NULL) \
{ \
	VULKAN_WARN.println("Device PFN_" #PFNNAME " not available (Extension not specified in VkDeviceCreateInfo?)"); \
	this->PFNNAME = (PFN_##PFNNAME) internal::impldef_##PFNNAME; \
}

void VulkanDeviceFunctionSet::load(VkDevice vkdevice, const VulkanInstance &vkinstance)
{
	LOAD(vkGetDeviceQueue);
	LOAD(vkDestroyDevice);
	LOAD(vkDeviceWaitIdle);
}

VulkanDeviceFunctionSet::VulkanDeviceFunctionSet() = default;
VulkanDeviceFunctionSet::VulkanDeviceFunctionSet(const VulkanDeviceFunctionSet &fset) = default;
VulkanDeviceFunctionSet::VulkanDeviceFunctionSet(VulkanDeviceFunctionSet &&fset) = default;

VulkanDeviceFunctionSet& VulkanDeviceFunctionSet::operator=(const VulkanDeviceFunctionSet &fset) = default;
VulkanDeviceFunctionSet& VulkanDeviceFunctionSet::operator=(VulkanDeviceFunctionSet &&fset) = default;

VulkanDeviceFunctionSet::~VulkanDeviceFunctionSet() = default;