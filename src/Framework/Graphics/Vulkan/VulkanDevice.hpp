#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_DEVICE_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_DEVICE_HPP

#include "Config.hpp"

#include "VulkanInstance.hpp"
#include "VulkanDeviceFunctionSet.hpp"

namespace DevaFramework
{

	class VulkanDevice
	{
	private:

		VkDevice handle;
		VulkanDeviceFunctionSet vk;

	public:

		DEVA_FRAMEWORK_API VulkanDevice();
		DEVA_FRAMEWORK_API VulkanDevice(VkDevice handle, const VulkanInstance &vkInstance);

	};

}

#endif //DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_DEVICE_HPP