#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_PHYSICAL_DEVICE_TRAITS_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_PHYSICAL_DEVICE_TRAITS_HPP

#include "Config.hpp"

#include <vector>

namespace DevaFramework
{
	struct VulkanInstance;

	struct VulkanPhysicalDevice {
		VkPhysicalDevice handle;
		VkPhysicalDeviceProperties properties;
		VkPhysicalDeviceFeatures features;
		std::vector<VkQueueFamilyProperties> queueFamilyProperties;
		std::vector<VkExtensionProperties> extensionProperties;
		std::vector<VkLayerProperties> layerProperties;
		VkPhysicalDeviceMemoryProperties memoryProperties;
	};

	namespace Vulkan {

		struct PhysicalDeviceSurfaceProperties {
			std::vector<VkSurfaceFormatKHR> formats;
			VkSurfaceCapabilitiesKHR capabilities;
			std::vector<VkPresentModeKHR> presentModes;
		};

		DEVA_FRAMEWORK_API bool doesDeviceSupportExtension(const VulkanPhysicalDevice &pdev, const char * ext);
		DEVA_FRAMEWORK_API bool doesDeviceQueueSupportSurface(
			const VulkanInstance &inst, 
			const VulkanPhysicalDevice &pdev, 
			uint32_t queue, 
			VkSurfaceKHR surface);

		DEVA_FRAMEWORK_API VulkanPhysicalDevice getPhysicalDeviceStruct(const VulkanInstance &inst, VkPhysicalDevice pdev);
		DEVA_FRAMEWORK_API PhysicalDeviceSurfaceProperties getSurfaceProperties(const VulkanInstance &inst, const VulkanPhysicalDevice &pdev, VkSurfaceKHR surface);

		DEVA_FRAMEWORK_API std::string toString(const VulkanPhysicalDevice &pdev);
	}
}

#endif //DEVA_FRAMEWORK_GRAPHICS_VULKAN_PHYSICAL_DEVICE_TRAITS_HPP
