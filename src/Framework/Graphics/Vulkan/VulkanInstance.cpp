#include "VulkanInstance.hpp"

using namespace DevaFramework;
using Vulkan::LOG_VULKAN;

#define ERRCHK if( result != VK_SUCCESS ) throw DevaException("DevaFramework::VulkanInstance failed because of Vulkan. Check logs for more info.");

namespace
{
	const VkApplicationInfo DEFAULT_APPLICATION_INFO =
	{
		VK_STRUCTURE_TYPE_APPLICATION_INFO,
		NULL,
		"Vulkan Application",
		VK_MAKE_VERSION(1, 0, 0),
		"Deva Engine",
		VK_MAKE_VERSION(1, 0, 0),
		VK_MAKE_VERSION(1, 0, 13)
	};

	const VkInstanceCreateInfo DEFAULT_INSTANCE_CREATE_INFO =
	{
		VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		NULL,
		0,
		&DEFAULT_APPLICATION_INFO,
		0,
		NULL,
		0,
		NULL
	};

	std::vector<VulkanPhysicalDevice> getPhysicalDeviceTraits(const VulkanInstance &inst) {
		VkResult result;

		VkInstance in = inst.handle;
		auto& vk = inst.vk;

		LOG_VULKAN.v("Enumerating physical devices (count)...");
		uint32_t device_count = 0;
		result = vk.vkEnumeratePhysicalDevices(in, &device_count, NULL);
		ERRCHK;

		if (device_count == 0) {
			throw DevaException(std::string("No physical devices available."));
		}

		LOG_VULKAN.v("System has " + strf(device_count) + " devices.");

		LOG_VULKAN.v("Enumerating physical devices (mHandles)...");
		std::vector<VkPhysicalDevice> deviceHandles(device_count);
		result = vk.vkEnumeratePhysicalDevices(in, &device_count, &deviceHandles[0]);
		ERRCHK;

		std::vector<VulkanPhysicalDevice> pdevs;
		for (uint32_t i = 0; i <= device_count - 1; i++)
		{
			pdevs.emplace_back(Vulkan::getPhysicalDeviceStruct(inst, deviceHandles[i]));
		}

		return pdevs;
	}
}

VulkanInstance Vulkan::createInstanceDefault()
{
	return createInstance(DEFAULT_INSTANCE_CREATE_INFO);
}

VulkanInstance Vulkan::createInstance(const VkInstanceCreateInfo &info)
{
	LOG_VULKAN.v("Creating VulkanInstance...");

	VulkanInstance instance;

	if (!internal::vkCreateInstance)
		throw DevaProgrammerErrorException("Vulkan not initialized (did you call DevaFramework::loadVulkan()?)");

	std::vector<std::string> extensions;
	for (uint32_t i = 0;i < info.enabledExtensionCount;i++)
	{
		extensions.push_back(*(info.ppEnabledExtensionNames + i));
		if (!Vulkan::instanceExtensionAvailable(extensions[i]))
			throw DevaExternalFailureException("Vulkan", "Could not create VkInstance - extension " + extensions[i] + " not supported by system.");
	}

	auto result = internal::vkCreateInstance(&info, NULL, &instance.handle);
	ERRCHK;

	LOG_VULKAN.v("Loading instance-local functions...");
	instance.vk = VulkanInstanceFunctionSet::load(instance.handle);
	instance.physicalDevices = getPhysicalDeviceTraits(instance);
	LOG_VULKAN.i("Successfully initialized VulkanInstance");

	return instance;
}

void Vulkan::destroyObject(VulkanInstance &instance) {
	instance.vk.vkDestroyInstance(instance.handle, nullptr);
	instance.handle = VK_NULL_HANDLE;
}