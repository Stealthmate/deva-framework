#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_DEVICE_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_DEVICE_HPP

#include "Config.hpp"

#include "VulkanInstance.hpp"
#include "VulkanDeviceFunctionSet.hpp"

namespace DevaFramework
{

	class VulkanDevice
	{
	private:

		VkDevice mHandle;
		VulkanDeviceFunctionSet mVk;
		
	public:
		DEVA_FRAMEWORK_API VulkanDevice();
		DEVA_FRAMEWORK_API VulkanDevice(VkDevice handle, const VulkanInstance &vkInstance);
		VulkanDevice(const VulkanDevice &dev) = delete;
		DEVA_FRAMEWORK_API VulkanDevice(VulkanDevice &&dev);
		VulkanDevice& operator=(const VulkanDevice &dev) = delete;
		DEVA_FRAMEWORK_API VulkanDevice& operator=(VulkanDevice &&dev);
		DEVA_FRAMEWORK_API ~VulkanDevice();

		DEVA_FRAMEWORK_API VulkanDeviceFunctionSet vk() const;
		DEVA_FRAMEWORK_API VkDevice handle() const;

		DEVA_FRAMEWORK_API std::vector<VkQueue> renderQueues() const;
		DEVA_FRAMEWORK_API std::vector<VkQueue> computeQueues() const;
		DEVA_FRAMEWORK_API std::vector<VkQueue> transferQueues() const;
		DEVA_FRAMEWORK_API std::vector<VkQueue> sparseBindingQueues() const;

	};

}

#endif //DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_DEVICE_HPP