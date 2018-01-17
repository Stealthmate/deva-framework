#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_DEVICE_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_DEVICE_HPP

#include "Config.hpp"
#include "VulkanObject.hpp"
#include "VulkanInstance.hpp"
#include "VulkanDeviceFunctionSet.hpp"
#include "VulkanDeviceQueue.hpp"

namespace DevaFramework
{
	struct VulkanDeviceInfo {
		std::vector<VulkanDeviceQueue> queues;
		VulkanPhysicalDeviceTraits physicalDeviceTraits;
	};

	class VulkanDevice : public VulkanObject<VkDevice, VulkanDeviceInfo> {
	public:
		DEVA_FRAMEWORK_API VulkanDevice() noexcept;
		DEVA_FRAMEWORK_API VulkanDevice(const VulkanInstance &vkInstance, const VulkanPhysicalDeviceTraits &pdev, const VkDeviceCreateInfo &createInfo);
		DEVA_FRAMEWORK_API VulkanDevice(VulkanDevice &&dev) noexcept;
		DEVA_FRAMEWORK_API VulkanDevice& operator=(VulkanDevice &&dev) noexcept;
		DEVA_FRAMEWORK_API ~VulkanDevice();
		DEVA_FRAMEWORK_API void swap(VulkanDevice &rhs);


		DEVA_FRAMEWORK_API const VulkanDeviceFunctionSet& vk() const noexcept;
		DEVA_FRAMEWORK_API std::vector<VulkanDeviceQueue> getQueuesOfFamily(VkQueueFlagBits type) const;

	private:
		VulkanDeviceFunctionSet mVk;
	};

	DEVA_FRAMEWORK_API void swap(VulkanDevice &lhs, VulkanDevice &rhs);

	//Immutable
	/*
	class VulkanDevice
	{
	public:

		DEVA_FRAMEWORK_API VulkanDevice() noexcept;
		DEVA_FRAMEWORK_API VulkanDevice(const VulkanInstance &vkInstance, const VulkanPhysicalDeviceTraits &pdev, const VkDeviceCreateInfo &createInfo);
		DEVA_FRAMEWORK_API VulkanDevice(VulkanDevice &&dev) noexcept;
		DEVA_FRAMEWORK_API VulkanDevice& operator=(VulkanDevice &&dev) noexcept;
		DEVA_FRAMEWORK_API ~VulkanDevice();

		DEVA_FRAMEWORK_API VkDevice handle() const noexcept { return mHandle; }
		DEVA_FRAMEWORK_API const VulkanDeviceFunctionSet& vk() const noexcept { return mVk; }
		DEVA_FRAMEWORK_API const std::vector<VulkanDeviceQueue>& queues() const noexcept { return mQueues; }
		DEVA_FRAMEWORK_API const VulkanPhysicalDeviceTraits& physicalDeviceTraits() const noexcept { return mPhysicalDeviceTraits; }

		DEVA_FRAMEWORK_API std::vector<VulkanDeviceQueue> getQueuesOfFamily(VkQueueFlagBits type) const;


	private:
		VkDevice mHandle;
		VulkanDeviceFunctionSet mVk;
		std::vector<VulkanDeviceQueue> mQueues;
		VulkanPhysicalDeviceTraits mPhysicalDeviceTraits;

		VulkanDevice(const VulkanDevice &dev) = delete;
		VulkanDevice& operator=(const VulkanDevice &dev) = delete;
	};*/

}

#endif //DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_DEVICE_HP
