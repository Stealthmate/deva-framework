#ifndef DEVA_FRAMEWORK_GRAPHICS_INIT_H
#define DEVA_FRAMEWORK_GRAPHICS_INIT_H

#include "Config.hpp"

#include "Vulkan/VulkanPhysicalDevice.hpp"

#include <vector>

namespace DevaFramework {

	class GraphicsState
	{
		static VkInstance this_instance;
		static std::vector<VulkanPhysicalDevice> available_physical_devices;

		static void initVulkan(const VkInstanceCreateInfo &vulkan_info);

	public:

		//DEVA_FRAMEWORK_API static VkInstanceCreateInfo DEFAULT_INSTANCE_SETTINGS;
		//DEVA_FRAMEWORK_API static size_t getPhysicalDeviceCount();
		//
		//DEVA_FRAMEWORK_API static const VulkanPhysicalDeviceTraits& getPhysicalDevice(uint32_t i);
	};

}

#endif //DEVA_FRAMEWORK_GRAPHICS_MAIN_H