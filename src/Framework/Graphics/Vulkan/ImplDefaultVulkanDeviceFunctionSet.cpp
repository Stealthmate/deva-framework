#include "ImplDefaultVulkanDeviceFunctionSet.hpp"

using namespace DevaFramework;

void DevaFramework::internal::impldef_vkGetDeviceQueue(VkDevice device, uint32_t queueFamilyIndex, uint32_t queueIndex, VkQueue* pQueue)
{
	VULKAN_ERR.println("Called vkGetDeviceQueue with invalid driver PFN");
}

void DevaFramework::internal::impldef_vkDestroyDevice(VkDevice device, const VkAllocationCallbacks* pAllocator)
{
	VULKAN_ERR.println("Called vkDestroyDevice with invalid driver PFN");
}

VkResult DevaFramework::internal::impldef_vkDeviceWaitIdle(VkDevice device)
{
	VULKAN_ERR.println("Called vkDeviceWaitIdle with invalid driver PFN");
	return VK_SUCCESS;
}