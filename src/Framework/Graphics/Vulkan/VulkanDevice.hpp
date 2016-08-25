#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_DEVICE_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_DEVICE_HPP

#include "Config.hpp"

#include "VulkanPhysicalDevice.hpp"

namespace DevaFramework
{

	class VulkanDevice
	{
	public:

#include "DeviceFunctionSet.inl"

	private:

		VkDevice handle;

	public:

		DEVA_FRAMEWORK_API VulkanDevice(VkDevice handle);

	};

}

#endif //DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_DEVICE_HPP