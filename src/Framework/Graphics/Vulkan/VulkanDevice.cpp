#include "VulkanDevice.hpp"

using namespace DevaFramework;

VulkanDevice::VulkanDevice() noexcept : mHandle(VK_NULL_HANDLE) {}

VulkanDevice::VulkanDevice(const VulkanInstance &vkInstance, const VulkanPhysicalDeviceTraits &pdev, const VkDeviceCreateInfo &createInfo)
{
	VkResult result = vkInstance.vk().vkCreateDevice(pdev.handle(), &createInfo, nullptr, &mHandle);
	if (result != VK_SUCCESS)
	{
		throw DevaException("Could not create VkDevice!");
	}

	mVk = VulkanDeviceFunctionSet::load(mHandle, vkInstance);
	mPhysicalDeviceTraits = pdev;

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
			VulkanDeviceQueue queue{};
			queue.mParentDevice = mHandle;
			queue.mHandle = qhandle;
			queue.mFamilyIndex = qfami;
			queue.mIndex = j;
			queue.mType = pdev.queueFamilyProperties()[i].queueFlags;
			queue.mPriority = prio;
			mQueues.push_back(queue);
		}
	}
}

VulkanDevice::VulkanDevice(VulkanDevice &&dev) noexcept
	:mHandle(dev.mHandle),
	mVk(dev.mVk),
	mQueues(dev.mQueues),
	mPhysicalDeviceTraits(std::move(dev.mPhysicalDeviceTraits))
{
	dev.mHandle = VK_NULL_HANDLE;
}

VulkanDevice& VulkanDevice::operator=(VulkanDevice &&dev) noexcept {
	mHandle = dev.mHandle;
	mVk = dev.mVk;
	mQueues = dev.mQueues;
	mPhysicalDeviceTraits = std::move(dev.mPhysicalDeviceTraits);

	dev.mHandle = VK_NULL_HANDLE;
	
	return *this;
}

std::vector<VulkanDeviceQueue> VulkanDevice::getQueuesOfFamily(VkQueueFlagBits type) const
{
	std::vector<VulkanDeviceQueue> queues;
	for (auto & q : this->mQueues)
	{
		if (q.type() & type) queues.push_back(q);
	}
	return queues;
}

VulkanDevice::~VulkanDevice()
{
	if (mHandle != VK_NULL_HANDLE) {
		mVk.vkDestroyDevice(mHandle, nullptr);
	}
}