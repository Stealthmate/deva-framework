#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_PHYSICAL_DEVICE_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_PHYSICAL_DEVICE_HPP

#include "Config.hpp"

#include <vector>

namespace DevaFramework
{
	struct VulkanPhysicalDevice
	{

		const VkPhysicalDevice handle;
		const VkPhysicalDeviceProperties properties;
		const VkPhysicalDeviceFeatures features;
		const std::vector<VkQueueFamilyProperties> queueFamilies;

		DEVA_FRAMEWORK_API VulkanPhysicalDevice(
			VkPhysicalDevice handle,
			const VkPhysicalDeviceProperties &properties,
			const VkPhysicalDeviceFeatures &features,
			const std::vector<VkQueueFamilyProperties> &queueFamilies) 
			: handle(handle), 
			properties(properties), 
			features(features), 
			queueFamilies(queueFamilies) {}

		DEVA_FRAMEWORK_API std::string to_string() const;
	};


}

#endif //DEVA_FRAMEWORK_GRAPHICS_VULKAN_PHYSICAL_DEVICE_HPP