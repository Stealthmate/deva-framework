#include "VulkanDevice.hpp"

#include "../../Exceptions.hpp"

using namespace DevaFramework;

VulkanDevice::VulkanDevice()
{
	this->handle = VK_NULL_HANDLE;
}

VulkanDevice::VulkanDevice(VulkanDevice &&dev)
{
	this->handle = dev.handle;
	this->vk = dev.vk;

	dev.handle = VK_NULL_HANDLE;
	dev.vk = VulkanDeviceFunctionSet();
}

VulkanDevice::VulkanDevice(VkDevice dev, const VulkanInstance &vkinstance) : handle(dev)
{
	vk = VulkanDeviceFunctionSet::load(dev, vkinstance);
}

VulkanDevice& VulkanDevice::operator=(VulkanDevice &&dev)
{
	this->handle = dev.handle;
	this->vk = dev.vk;
	
	dev.handle = VK_NULL_HANDLE;
	dev.vk = VulkanDeviceFunctionSet();

	return *this;
}

VulkanDeviceFunctionSet VulkanDevice::getFunctionSet() const
{
	return vk;
}

VkDevice VulkanDevice::getHandle() const
{
	return this->handle;
}

VulkanDevice::~VulkanDevice()
{
	if (handle != VK_NULL_HANDLE) {
		vk.vkDestroyDevice(handle, nullptr);
	}
	handle = VK_NULL_HANDLE;
}