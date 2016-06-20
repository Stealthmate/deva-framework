#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_PHYSICAL_DEVICE_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_PHYSICAL_DEVICE_HPP

#include "Config.hpp"

#include <vector>

namespace DevaFramework
{
	struct VulkanPhysicalDevice
	{

	private:

		const VkPhysicalDevice handle;
		const VkPhysicalDeviceProperties properties;
		const VkPhysicalDeviceFeatures features;
		const std::vector<VkQueueFamilyProperties> queueFamilies;

	public:
		DEVA_FRAMEWORK_API VulkanPhysicalDevice();
		DEVA_FRAMEWORK_API VulkanPhysicalDevice(
			const VkPhysicalDevice &handle,
			const VkPhysicalDeviceProperties &props, 
			const VkPhysicalDeviceFeatures &feats,
			const std::vector<VkQueueFamilyProperties> &queueFamilies);

		DEVA_FRAMEWORK_API const VkPhysicalDevice getHandle() const;
		DEVA_FRAMEWORK_API const VkPhysicalDeviceProperties getProperties() const;
		DEVA_FRAMEWORK_API const VkPhysicalDeviceFeatures getFeatures() const;
		DEVA_FRAMEWORK_API int getQueueFamiliyCount() const;
		DEVA_FRAMEWORK_API const VkQueueFamilyProperties& getQueueFamiliy(int i) const;

		DEVA_FRAMEWORK_API std::string to_string() const;
	};


}

#endif //DEVA_FRAMEWORK_GRAPHICS_VULKAN_PHYSICAL_DEVICE_HPP