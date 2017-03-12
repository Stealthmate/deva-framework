#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_PHYSICAL_DEVICE_TRAITS_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_PHYSICAL_DEVICE_TRAITS_HPP

#include "Config.hpp"

#include <vector>

namespace DevaFramework
{
	class VulkanInstance;

	//Immutable

	struct VulkanPhysicalDeviceTraits
	{
		struct SurfaceProperties {
			std::vector<VkSurfaceFormatKHR> formats;
			VkSurfaceCapabilitiesKHR capabilities;
			std::vector<VkPresentModeKHR> presentModes;
		};

		DEVA_FRAMEWORK_API static VulkanPhysicalDeviceTraits forDevice(const VulkanInstance &vkInstance, VkPhysicalDevice handle);

		DEVA_FRAMEWORK_API VulkanPhysicalDeviceTraits();
		DEVA_FRAMEWORK_API VulkanPhysicalDeviceTraits(const VulkanPhysicalDeviceTraits &pdev);
		DEVA_FRAMEWORK_API VulkanPhysicalDeviceTraits(VulkanPhysicalDeviceTraits &&pdev);
		DEVA_FRAMEWORK_API VulkanPhysicalDeviceTraits& operator=(const VulkanPhysicalDeviceTraits &pdev);
		DEVA_FRAMEWORK_API VulkanPhysicalDeviceTraits& operator=(VulkanPhysicalDeviceTraits &&pdev);
		DEVA_FRAMEWORK_API ~VulkanPhysicalDeviceTraits();

		DEVA_FRAMEWORK_API VkPhysicalDevice handle() const { return mHandle; }
		DEVA_FRAMEWORK_API const VkPhysicalDeviceProperties& properties() const { return mProperties; }
		DEVA_FRAMEWORK_API const VkPhysicalDeviceFeatures& features() const { return mFeatures; }
		DEVA_FRAMEWORK_API const std::vector<VkQueueFamilyProperties>& queueFamilyProperties() const { return mQueueFamilyProperties; }
		DEVA_FRAMEWORK_API const std::vector<VkExtensionProperties>& extensionProperties() const { return mExtensionProperties; }
		DEVA_FRAMEWORK_API const std::vector<VkLayerProperties>& layerProperties() const { return mLayerProperties; }
		DEVA_FRAMEWORK_API const VkPhysicalDeviceMemoryProperties& memoryProperties() const { return mMemoryProperties; }

		DEVA_FRAMEWORK_API SurfaceProperties getSurfaceProperties(const VulkanInstance &vkInstance, VkSurfaceKHR surface) const;

		DEVA_FRAMEWORK_API std::string to_string() const;

	private:

		VkPhysicalDevice mHandle;
		VkPhysicalDeviceProperties mProperties;
		VkPhysicalDeviceFeatures mFeatures;
		std::vector<VkQueueFamilyProperties> mQueueFamilyProperties;
		std::vector<VkExtensionProperties> mExtensionProperties;
		std::vector<VkLayerProperties> mLayerProperties;
		VkPhysicalDeviceMemoryProperties mMemoryProperties;
	};


}

#endif //DEVA_FRAMEWORK_GRAPHICS_VULKAN_PHYSICAL_DEVICE_TRAITS_HPP
