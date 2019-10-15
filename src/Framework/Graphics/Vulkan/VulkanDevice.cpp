#include "VulkanDevice.hpp"

#include "VulkanInstance.hpp"
#include "VulkanDeviceFunctionSet.hpp"
#include "VulkanDeviceQueue.hpp"
#include "VulkanPhysicalDevice.hpp"

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
		std::vector<VulkanQueue> inqueues;
		for (uint32_t j = 0;j < qcount;j++)
		{
			float prio = createInfo.pQueueCreateInfos[i].pQueuePriorities[j];

			VulkanQueue queue;
			queue.parentDevice = device.handle;
			queue.familyIndex = qfami;
			queue.index = j;
			queue.type = pdev.queueFamilyProperties[i].queueFlags;
			queue.priority = prio;

			device.vk.vkGetDeviceQueue(device.handle, qfami, j, &queue.handle);

			inqueues.push_back(queue);
		}
		device.queues.push_back(inqueues);
	}

	return device;
}

VulkanQueue Vulkan::getDeviceQueue(const VulkanDevice &dev, uint32_t family, uint32_t index) {
	return dev.queues[family][index];
}

std::vector<std::pair<uint32_t, uint32_t>> Vulkan::getQueuesOfType(const VulkanDevice &dev, VkQueueFlags flags) {
	std::vector<std::pair<uint32_t, uint32_t>> res;

	for (auto i : dev.queues) {
		for (auto q : i) {
			if (flags & q.type) {
				res.push_back({ q.familyIndex, q.index });
			}
		}
	}

	return res;
}

void Vulkan::destroyObject(VulkanDevice &dev) {
	dev.vk.vkDestroyDevice(dev.handle, nullptr);
	dev.handle = VK_NULL_HANDLE;
}