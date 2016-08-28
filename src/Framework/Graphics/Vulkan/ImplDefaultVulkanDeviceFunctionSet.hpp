#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_IMPL_DEFAULT_VULKAN_DEVICE_FUNCTION_SET_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_IMPL_DEFAULT_VULKAN_DEVICE_FUNCTION_SET_HPP

#include "Config.hpp"

namespace DevaFramework
{
	namespace internal
	{
		void impldef_vkGetDeviceQueue(VkDevice device, uint32_t queueFamilyIndex, uint32_t queueIndex, VkQueue* pQueue);
		void impldef_vkDestroyDevice(VkDevice device, const VkAllocationCallbacks* pAllocator);
		VkResult impldef_vkDeviceWaitIdle(VkDevice device);

	}
}

#endif //DEVA_FRAMEWORK_GRAPHICS_VULKAN_IMPL_DEFAULT_VULKAN_DEVICE_FUNCTION_SET_HPP