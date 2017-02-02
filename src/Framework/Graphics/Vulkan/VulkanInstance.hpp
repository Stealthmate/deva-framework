#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_INSTANCE
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_INSTANCE

#include "Config.hpp"

#include "VulkanPhysicalDevice.hpp"
#include "InstanceFunctionSet.hpp"

namespace DevaFramework
{
	class VulkanInstance
	{
		VkInstance mHandle;
		VulkanInstanceFunctionSet mVk;

		std::vector<VulkanPhysicalDeviceWrapper> physical_devices;

		void populatePDeviceList();

		VulkanInstance(const VkInstanceCreateInfo &info);

	public: 

		DEVA_FRAMEWORK_API static VulkanInstance create(); //This DOES create a valid VkInstance, with implementation-defined default createinfo
		DEVA_FRAMEWORK_API static VulkanInstance create(const VkInstanceCreateInfo &info);

		DEVA_FRAMEWORK_API VulkanInstance(VkInstance handle); //Wraps the handle
		DEVA_FRAMEWORK_API VulkanInstance(); //This does NOT create a valid VkInstance. This only creates an empty object.
		DEVA_FRAMEWORK_API VulkanInstance(const VulkanInstance &vkinstance)             = delete;
		DEVA_FRAMEWORK_API VulkanInstance(VulkanInstance &&vkinstance);
		DEVA_FRAMEWORK_API VulkanInstance& operator=(const VulkanInstance &vkinstance)  = delete;
		DEVA_FRAMEWORK_API VulkanInstance& operator=(VulkanInstance &&vkinstance);
		DEVA_FRAMEWORK_API ~VulkanInstance();

		DEVA_FRAMEWORK_API std::vector<VulkanPhysicalDeviceWrapper> getPhysicalDevices() const;

		DEVA_FRAMEWORK_API const VulkanInstanceFunctionSet& vk() const;
		DEVA_FRAMEWORK_API VkInstance handle() const;

		DEVA_FRAMEWORK_API void destroy();
	};
}



#endif //DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_INSTANCE
