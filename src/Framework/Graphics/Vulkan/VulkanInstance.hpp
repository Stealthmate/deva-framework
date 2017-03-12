#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_INSTANCE
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_INSTANCE

#include "Config.hpp"

#include "VulkanPhysicalDevice.hpp"
#include "InstanceFunctionSet.hpp"

namespace DevaFramework
{

	//Immutable

	class VulkanInstance
	{
	public:

		DEVA_FRAMEWORK_API static VulkanInstance createDefault();
		DEVA_FRAMEWORK_API static VulkanInstance create(const VkInstanceCreateInfo &info);

		DEVA_FRAMEWORK_API VulkanInstance() noexcept;
		DEVA_FRAMEWORK_API VulkanInstance(VulkanInstance &&vkinstance) noexcept;
		DEVA_FRAMEWORK_API VulkanInstance& operator=(VulkanInstance &&vkinstance) noexcept;
		DEVA_FRAMEWORK_API ~VulkanInstance();

		DEVA_FRAMEWORK_API std::vector<VulkanPhysicalDeviceTraits> getPhysicalDevices() const;

		DEVA_FRAMEWORK_API VkInstance handle() const noexcept { return mHandle; }
		DEVA_FRAMEWORK_API const VulkanInstanceFunctionSet& vk() const noexcept { return mVk; }

		DEVA_FRAMEWORK_API void destroy();

	private:

		VkInstance mHandle;
		VulkanInstanceFunctionSet mVk;

		std::vector<VulkanPhysicalDeviceTraits> physical_devices;

		void populatePDeviceList();

		VulkanInstance(VkInstance handle); //Wraps the handle
		VulkanInstance(const VkInstanceCreateInfo &info);
		VulkanInstance(const VulkanInstance &vkinstance) = delete;
		VulkanInstance& operator=(const VulkanInstance &vkinstance) = delete;
	};
}



#endif //DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_INSTANCE
