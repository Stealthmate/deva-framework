#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_DEVICE_QUEUE_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_DEVICE_QUEUE_HPP

#include "Config.hpp"

namespace DevaFramework
{

	//Immutable

	struct VulkanDeviceQueue
	{
		friend class VulkanDevice;

		DEVA_FRAMEWORK_API VkDevice parentDevice() const { return mParentDevice; }
		DEVA_FRAMEWORK_API VkQueue handle() const { return mHandle; }
		DEVA_FRAMEWORK_API uint32_t familyIndex() const { return mFamilyIndex; }
		DEVA_FRAMEWORK_API uint32_t index() const { return mIndex; }
		DEVA_FRAMEWORK_API VkQueueFlags type() const { return mType; }
		DEVA_FRAMEWORK_API float priority() const { return mPriority; }

	private:

		VkDevice mParentDevice;
		VkQueue mHandle;
		uint32_t mFamilyIndex;
		uint32_t mIndex;
		VkQueueFlags mType;
		float mPriority;
	};

}

#endif //DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_DEVICE_QUEUE_HPP
