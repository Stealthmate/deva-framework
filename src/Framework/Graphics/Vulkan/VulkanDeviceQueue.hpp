#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_DEVICE_QUEUE_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_DEVICE_QUEUE_HPP

#include "Config.hpp"

namespace DevaFramework
{
	struct VulkanDeviceQueueWrapper
	{
		friend class VulkanDevice;

		const VkDevice mParentDevice;
		const VkQueue mHandle;
		const uint32_t mFamilyIndex;
		const uint32_t mIndex;
		const VkQueueFlags mType;
		
		const float mPriority;

	private:
		VulkanDeviceQueueWrapper(
			VkDevice parentDevice,
			VkQueue handle,
			uint32_t familyIndex,
			uint32_t index,
			float priority,
			VkQueueFlags type
		) : mParentDevice(parentDevice), mHandle(handle), mFamilyIndex(familyIndex), mIndex(index), mPriority(priority), mType(type) {}

	};
}

#endif //DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_DEVICE_QUEUE_HPP
