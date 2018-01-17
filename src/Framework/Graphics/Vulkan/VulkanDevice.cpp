#include "VulkanDevice.hpp"

using namespace DevaFramework;

VulkanDevice::VulkanDevice() noexcept {}

const VulkanDeviceFunctionSet& VulkanDevice::vk() const noexcept {
	return mVk;
}

VulkanDevice::VulkanDevice(const VulkanInstance &vkInstance, const VulkanPhysicalDeviceTraits &pdev, const VkDeviceCreateInfo &createInfo)
{
	VkResult result = vkInstance.vk().vkCreateDevice(pdev.handle(), &createInfo, nullptr, &mHandle);
	if (result != VK_SUCCESS)
	{
		throw DevaException("Could not create VkDevice!");
	}

	mVk = VulkanDeviceFunctionSet::load(mHandle, vkInstance);

	mInfo.physicalDeviceTraits = pdev;

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
			mInfo.queues.push_back(queue);
		}
	}

}

VulkanDevice::VulkanDevice(VulkanDevice &&dev) noexcept
	: VulkanObject(std::move(dev)),
	mVk(dev.mVk)
{
	dev.mVk = VulkanDeviceFunctionSet();
}

VulkanDevice& VulkanDevice::operator=(VulkanDevice &&dev) noexcept {
	swap(dev);
	return *this;
}

std::vector<VulkanDeviceQueue> VulkanDevice::getQueuesOfFamily(VkQueueFlagBits type) const
{
	std::vector<VulkanDeviceQueue> queues;
	for (auto & q : this->mInfo.queues)
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

void VulkanDevice::swap(VulkanDevice &rhs) {
	using std::swap;
	VulkanObject::swap(rhs);
	swap(mVk, rhs.mVk);
}

void DevaFramework::swap(VulkanDevice &lhs, VulkanDevice &rhs) {
	lhs.swap(rhs);
}