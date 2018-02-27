#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_DEVICE_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_DEVICE_HPP

#include "Config.hpp"

#include "VulkanDeviceFunctionSet.hpp"
#include "VulkanPhysicalDevice.hpp"
#include "VulkanDeviceQueue.hpp"

namespace DevaFramework
{
	struct VulkanInstance;
	struct VulkanDeviceFunctionSet;

	struct VulkanDevice {

		VkDevice handle;
		VulkanDeviceFunctionSet vk;
		std::vector<std::vector<VulkanQueue>> queues;
		VulkanPhysicalDevice physicalDevice;
	};

	namespace Vulkan {

		DEVA_FRAMEWORK_API VulkanDevice createDevice(
			const VulkanInstance &vkInstance, 
			const VulkanPhysicalDevice &pdev, 
			const VkDeviceCreateInfo &createInfo);

		DEVA_FRAMEWORK_API std::vector<std::pair<uint32_t, uint32_t>> getQueuesOfType(const VulkanDevice &dev, VkQueueFlags type);

		DEVA_FRAMEWORK_API VulkanQueue getDeviceQueue(const VulkanDevice &dev, uint32_t family, uint32_t index);

		DEVA_FRAMEWORK_API void destroyObject(VulkanDevice &dev);
	}
}

#endif //DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_DEVICE_HP
