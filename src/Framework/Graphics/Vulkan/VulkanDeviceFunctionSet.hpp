#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_DEVICE_FUNCTION_SET_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_DEVICE_FUNCTION_SET_HPP

#include "Config.hpp"

#include "VulkanInstance.hpp"

namespace DevaFramework
{
	struct VulkanDeviceFunctionSet
	{

		PFN_vkGetDeviceQueue vkGetDeviceQueue;
		PFN_vkDestroyDevice vkDestroyDevice;
		PFN_vkDeviceWaitIdle vkDeviceWaitIdle;


		DEVA_FRAMEWORK_API VulkanDeviceFunctionSet();
		DEVA_FRAMEWORK_API VulkanDeviceFunctionSet(const VulkanDeviceFunctionSet &fset);
		DEVA_FRAMEWORK_API VulkanDeviceFunctionSet(VulkanDeviceFunctionSet &&fset);

		DEVA_FRAMEWORK_API VulkanDeviceFunctionSet& operator=(const VulkanDeviceFunctionSet &fset);
		DEVA_FRAMEWORK_API VulkanDeviceFunctionSet& operator=(VulkanDeviceFunctionSet &&fset);

		DEVA_FRAMEWORK_API ~VulkanDeviceFunctionSet();

		DEVA_FRAMEWORK_API void load(VkDevice vkDevice, const VulkanInstance &vkInstance);
	};
}

#endif //DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_DEVICE_FUNCTION_SET_HPP