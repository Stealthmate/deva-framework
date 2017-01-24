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
		VulkanDevice(const VulkanDevice &dev) = delete;
		DEVA_FRAMEWORK_API VulkanDevice(VulkanDevice &&dev);
		VulkanDevice& operator=(const VulkanDevice &dev) = delete;
		DEVA_FRAMEWORK_API VulkanDevice& operator=(VulkanDevice &&dev);
		DEVA_FRAMEWORK_API ~VulkanDevice();

		DEVA_FRAMEWORK_API VulkanDeviceFunctionSet getFunctionSet() const;
		DEVA_FRAMEWORK_API VkDevice getHandle() const;

	};

}

#endif //DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_DEVICE_HPP