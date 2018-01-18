#include "VulkanDevice.hpp"

using namespace DevaFramework;

VulkanDevice Vulkan::createDevice(
	const VulkanInstance &vkInstance, 
	const VulkanPhysicalDevice &pdev,
	const VkDeviceCreateInfo &createInfo)
{

	VulkanDevice device;

	VkResult result = vkInstance.vk.vkCreateDevice(pdev.handle, &createInfo, nullptr, &device.handle);
	if (result != VK_SUCCESS)
	{
		throw DevaException("Could not create VkDevice!");
	}

	device.vk = VulkanDeviceFunctionSet::load(device.handle, vkInstance);

	device.physicalDevice = pdev;

	uint32_t nqci = createInfo.queueCreateInfoCount;
	for (uint32_t i = 0;i < nqci;i++)
	{
		uint32_t qfami = createInfo.pQueueCreateInfos[i].queueFamilyIndex;
		uint32_t qcount = createInfo.pQueueCreateInfos[i].queueCount;
		for (uint32_t j = 0;j < qcount;j++)
		{
			float prio = createInfo.pQueueCreateInfos[i].pQueuePriorities[j];

			VulkanQueue info;
			info.parentDevice = device.handle;
			info.familyIndex = qfami;
			info.index = j;
			info.type = pdev.queueFamilyProperties[i].queueFlags;
			info.priority = prio;
			device.queues.push_back(info);
		}
	}

	return device;
}

VkQueue Vulkan::getDeviceQueue(const VulkanDevice &dev, uint32_t family, uint32_t index) {
	VkQueue q;
	dev.vk.vkGetDeviceQueue(dev.handle, family, index, &q);
	return q;
}

std::vector<std::pair<uint32_t, uint32_t>> Vulkan::getQueuesOfType(const VulkanDevice &dev, VkQueueFlags flags) {
	std::vector<std::pair<uint32_t, uint32_t>> res;

	for (auto i = 0;i < dev.queues.size();i++) {
		auto q = dev.queues[i];
		if (flags & q.type) {
			res.push_back({q.familyIndex, q.index});
		}
	}

	return res;
}

void Vulkan::destroyObject(VulkanDevice &dev) {
	dev.vk.vkDestroyDevice(dev.handle, nullptr);
	dev.handle = VK_NULL_HANDLE;
}