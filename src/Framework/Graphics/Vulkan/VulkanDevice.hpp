#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_DEVICE_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_DEVICE_HPP

#include "Config.hpp"

#include "VulkanInstance.hpp"
#include "VulkanDeviceFunctionSet.hpp"
#include "VulkanDeviceQueue.hpp"

namespace DevaFramework
{

	class VulkanDevice
	{

	private:

		VkDevice mHandle;
		VulkanDeviceFunctionSet mVk;
		std::vector<VulkanDeviceQueueWrapper> mQueues;

	public:
		DEVA_FRAMEWORK_API VulkanDevice();
		DEVA_FRAMEWORK_API VulkanDevice(const VulkanInstance &vkInstance, const VulkanPhysicalDeviceWrapper &pdev, const VkDeviceCreateInfo &createInfo);
		VulkanDevice(const VulkanDevice &dev) = delete;
		DEVA_FRAMEWORK_API VulkanDevice(VulkanDevice &&dev);
		VulkanDevice& operator=(const VulkanDevice &dev) = delete;
		DEVA_FRAMEWORK_API VulkanDevice& operator=(VulkanDevice &&dev);
		DEVA_FRAMEWORK_API ~VulkanDevice();

		DEVA_FRAMEWORK_API const VulkanDeviceFunctionSet& vk() const;
		DEVA_FRAMEWORK_API VkDevice handle() const;

		DEVA_FRAMEWORK_API std::vector<VulkanDeviceQueueWrapper> getQueuesOfFamily(VkQueueFlagBits type) const;

	};

}

#endif //DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_DEVICE_HP
