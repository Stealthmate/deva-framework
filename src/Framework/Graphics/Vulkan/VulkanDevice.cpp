#include "VulkanDevice.hpp"

using namespace DevaFramework;

VulkanDevice::VulkanDevice() : mHandle(VK_NULL_HANDLE) {}

VulkanDevice::VulkanDevice(const VulkanInstance &vkInstance, const VulkanPhysicalDeviceWrapper &pdev, const VkDeviceCreateInfo &createInfo)
{
	VkResult result = vkInstance.vk().vkCreateDevice(pdev.handle, &createInfo, nullptr, &mHandle);
	if (result != VK_SUCCESS)
	{
		throw DevaException("Could not create VkDevice!");
	}
	mVk = VulkanDeviceFunctionSet::load(mHandle, vkInstance);
	uint32_t nqci = createInfo.queueCreateInfoCount;
	for (uint32_t i = 0;i < nqci;i++)
	{
		uint32_t qfami = createInfo.pQueueCreateInfos[i].queueFamilyIndex;
		uint32_t qcount = createInfo.pQueueCreateInfos[i].queueCount;
		for (uint32_t j = 0;j < qcount;j++)
		{
			float prio = createInfo.pQueueCreateInfos[i].pQueuePriorities[j];
			VkQueue qhandle;
			mVk.vkGetDeviceQueue(mHandle, qfami, j, &qhandle);
			mQueues.push_back(VulkanDeviceQueueWrapper(mHandle, qhandle, qfami, j, prio, pdev.queueFamilies[i].queueFlags));
		}
	}
}

VulkanDevice::VulkanDevice(VulkanDevice &&dev)
{
	mHandle = dev.mHandle;
	mVk = dev.mVk;
	mQueues = std::move(dev.mQueues);

	dev.mHandle = VK_NULL_HANDLE;
	dev.mVk = VulkanDeviceFunctionSet();
}

VulkanDevice& VulkanDevice::operator=(VulkanDevice &&dev)
{
	mHandle = dev.mHandle;
	mVk = dev.mVk;
	mQueues = std::move(dev.mQueues);

	dev.mHandle = VK_NULL_HANDLE;
	dev.mVk = VulkanDeviceFunctionSet();

	return *this;
}


const VulkanDeviceFunctionSet& VulkanDevice::vk() const
{
	return mVk;
}

VkDevice VulkanDevice::handle() const
{
	return mHandle;
}

std::vector<VulkanDeviceQueueWrapper> VulkanDevice::getQueuesOfFamily(VkQueueFlagBits type) const
{
	std::vector<VulkanDeviceQueueWrapper> queues;
	for (auto & q : mQueues)
	{
		if (q.mType & type) queues.push_back(q);
	}
	return queues;
}

VulkanDevice::~VulkanDevice()
{
	if (mHandle != VK_NULL_HANDLE) {
		mVk.vkDestroyDevice(mHandle, nullptr);
	}
	mHandle = VK_NULL_HANDLE;
}