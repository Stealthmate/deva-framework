#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_DEVICE_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_DEVICE_HPP

#include "Config.hpp"
#include "VulkanObject.hpp"
#include "VulkanInstance.hpp"
#include "VulkanDeviceFunctionSet.hpp"
#include "VulkanDeviceQueue.hpp"

namespace DevaFramework
{
	struct VulkanDevice {

		VkDevice handle;
		VulkanDeviceFunctionSet vk;
		std::vector<VulkanQueue> queues;
		VulkanPhysicalDevice physicalDevice;
	};

	namespace Vulkan {

		DEVA_FRAMEWORK_API VulkanDevice createDevice(
			const VulkanInstance &vkInstance, 
			const VulkanPhysicalDevice &pdev, 
			const VkDeviceCreateInfo &createInfo);

		DEVA_FRAMEWORK_API std::vector<std::pair<uint32_t, uint32_t>> getQueuesOfType(const VulkanDevice &dev, VkQueueFlags type);

		DEVA_FRAMEWORK_API VkQueue getDeviceQueue(const VulkanDevice &dev, uint32_t family, uint32_t index);

		DEVA_FRAMEWORK_API void destroyObject(VulkanDevice &dev);

		template<typename T>
		void destroyObject(const VulkanDevice &dev, T& obj) {
			static_assert("No overload found for type");
		}
	}

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

		DEVA_FRAMEWORK_API std::vector<VulkanDeviceQueue> getQueuesOfType(VkQueueFlagBits type) const;


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
