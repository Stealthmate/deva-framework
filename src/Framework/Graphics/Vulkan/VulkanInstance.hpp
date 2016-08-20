#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_INSTANCE
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_INSTANCE

#include "Config.hpp"
#include "VulkanPhysicalDevice.hpp"

#include "../../Window/Window.hpp"

namespace DevaFramework
{
	class VulkanInstance
	{
		friend class Window::ImplWindow;

	private:

		VkInstance handle;
		VkSurfaceKHR surface;

		std::vector<VulkanPhysicalDevice> physical_devices;

		VulkanInstance(const VkInstanceCreateInfo &info);

	public: 

		DEVA_FRAMEWORK_API static VulkanInstance create(); //This DOES create a valid VkInstance, with implementation-defined default createinfo
		DEVA_FRAMEWORK_API static VulkanInstance create(const VkInstanceCreateInfo &info);

		DEVA_FRAMEWORK_API VulkanInstance(); //This does NOT create a valid VkInstance. This only creates an empty object.
		DEVA_FRAMEWORK_API VulkanInstance(const VulkanInstance &vkinstance)             = delete;
		DEVA_FRAMEWORK_API VulkanInstance(VulkanInstance &&vkinstance)                  = default;
		DEVA_FRAMEWORK_API VulkanInstance& operator=(const VulkanInstance &vkinstance)  = delete;
		DEVA_FRAMEWORK_API VulkanInstance& operator=(VulkanInstance &&vkinstance)       = default;
		DEVA_FRAMEWORK_API ~VulkanInstance();

		DEVA_FRAMEWORK_API VkInstance getInstance() const;
		DEVA_FRAMEWORK_API const std::vector<VulkanPhysicalDevice> & getPhysicalDevices() const;
		DEVA_FRAMEWORK_API VkSurfaceKHR getSurface();
		DEVA_FRAMEWORK_API const VkSurfaceKHR getSurface() const;
	};
}



#endif //DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_INSTANCE