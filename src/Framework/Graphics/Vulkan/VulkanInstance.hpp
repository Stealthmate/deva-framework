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

		DEVA_FRAMEWORK_API static VulkanInstance create();
		DEVA_FRAMEWORK_API static VulkanInstance create(const VkInstanceCreateInfo &info);

		DEVA_FRAMEWORK_API VkInstance getInstance() const;
		DEVA_FRAMEWORK_API const std::vector<VulkanPhysicalDevice> & getPhysicalDevices() const;
	};
}



#endif //DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_INSTANCE