#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_PHYSICAL_DEVICE_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_PHYSICAL_DEVICE_HPP

#include "Config.hpp"

#include <vector>

namespace DevaFramework
{
	class VulkanInstance;

	struct VulkanPhysicalDeviceWrapper
	{
		struct SurfaceProperties {
			std::vector<VkSurfaceFormatKHR> formats;
			VkSurfaceCapabilitiesKHR capabilities;
			std::vector<VkPresentModeKHR> presentModes;
		};

		DEVA_FRAMEWORK_API static VulkanPhysicalDeviceWrapper fromHandle(const VulkanInstance &vkInstance, VkPhysicalDevice handle);

		VkPhysicalDevice handle;
		VkPhysicalDeviceType type;
		VkPhysicalDeviceProperties properties;
		VkPhysicalDeviceFeatures features;
		std::vector<VkQueueFamilyProperties> queueFamilies;
		std::vector<VkExtensionProperties> extensions;
		std::vector<VkLayerProperties> layers;

		DEVA_FRAMEWORK_API SurfaceProperties getSurfaceProperties(const VulkanInstance &vkInstance, VkSurfaceKHR surface);

		DEVA_FRAMEWORK_API std::string to_string() const;
	};


}

#endif //DEVA_FRAMEWORK_GRAPHICS_VULKAN_PHYSICAL_DEVICE_HPP
