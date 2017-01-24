#include "VulkanDevice.hpp"

#include "../../Exceptions.hpp"

using namespace DevaFramework;

VulkanDevice::VulkanDevice() : mHandle(VK_NULL_HANDLE) {}

VulkanDevice::VulkanDevice(VulkanDevice &&dev)
{
	mHandle = dev.mHandle;
	mVk = dev.mVk;

	dev.mHandle = VK_NULL_HANDLE;
	dev.mVk = VulkanDeviceFunctionSet();
}

VulkanDevice::VulkanDevice(VkDevice dev, const VulkanInstance &vkinstance) : mHandle(dev)
{
	mVk = VulkanDeviceFunctionSet::load(dev, vkinstance);
}

VulkanDevice& VulkanDevice::operator=(VulkanDevice &&dev)
{
	mHandle = dev.mHandle;
	mVk = dev.mVk;

	dev.mHandle = VK_NULL_HANDLE;
	dev.mVk = VulkanDeviceFunctionSet();

	return *this;
}


VulkanDeviceFunctionSet VulkanDevice::vk() const
{
	return mVk;
}

VkDevice VulkanDevice::handle() const
{
	return mHandle;
}

VulkanDevice::~VulkanDevice()
{
	if (mHandle != VK_NULL_HANDLE) {
		mVk.vkDestroyDevice(mHandle, nullptr);
	}
	mHandle = VK_NULL_HANDLE;
}