#include "VulkanInstance.hpp"
#include "../../Exceptions.hpp"

using namespace DevaFramework;

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
}

#define ERRCHK() if( result != VK_SUCCESS ) throw ex;

VulkanInstance VulkanInstance::create()
{
	return create(DEFAULT_INSTANCE_CREATE_INFO);
}

VulkanInstance VulkanInstance::create(const VkInstanceCreateInfo &info)
{
	return VulkanInstance(info);
}

VulkanInstance::VulkanInstance(const VkInstanceCreateInfo &info) : handle(VK_NULL_HANDLE), surface(VK_NULL_HANDLE)
{
	VkInstance instance_handle;

	if (!vkCreateInstance)
		throw DevaProgrammerErrorException(
			"Vulkan not initialized", 
			"DevaFramework::loadVulkan() not called?", 
			"Call DevaFramework::loadVulkan() before using the Vulkan wrappers", 
			"-");

	DevaException ex("DevaFramework::VulkanInstance failed because of Vulkan. Check logs for more info.");

	VULKAN_LOG.println("Getting VkInstance handle...");
	auto result = vkCreateInstance(&info, NULL, &instance_handle);
	ERRCHK();

	this->handle = instance_handle;

	VULKAN_LOG.println("Loading instance-local functions...");
	this->vk.load(this->handle);

	VULKAN_LOG.println("Enumerating physical devices (count)...");
	uint32_t device_count = 0;
	result = vk.vkEnumeratePhysicalDevices(instance_handle, &device_count, NULL);
	ERRCHK();

	if (device_count == 0) {
		throw DevaException(
			"No physical devices available.");
	}

	VULKAN_LOG.println("System has " + strm(device_count) + " devices.");

	VULKAN_LOG.println("Enumerating physical devices (handles)...");
	std::vector<VkPhysicalDevice> deviceHandles(device_count);
	result = vk.vkEnumeratePhysicalDevices(instance_handle, &device_count, &deviceHandles[0]);
	ERRCHK();

	VkPhysicalDeviceProperties deviceProperties;
	VkPhysicalDeviceFeatures deviceFeatures;
	std::vector<VkQueueFamilyProperties> queueFamilies;
	for (uint32_t i = 0; i <= device_count - 1; i++) 
	{

		VULKAN_LOG.println("Querying VkPhysicalDeviceProperties for device " + strm(i) + "...");
		vk.vkGetPhysicalDeviceProperties(deviceHandles[i], &deviceProperties);
		VULKAN_LOG.println("Querying VkPhysicalDeviceFeatures for device " + strm(i) + "...");
		vk.vkGetPhysicalDeviceFeatures(deviceHandles[i], &deviceFeatures);

		uint32_t queueFamilyCount = 0;
		VULKAN_LOG.println("Querying VkQueueFamilyProperties (count) for device " + strm(i) + "...");
		vk.vkGetPhysicalDeviceQueueFamilyProperties(deviceHandles[i], &queueFamilyCount, NULL);
		VULKAN_LOG.println("Device " + strm(i) + " supports " + strm(queueFamilyCount) + " queues");

		VULKAN_LOG.println("Querying VkQueueFamilyProperties (handles) for device " + strm(i) + "...");
		queueFamilies.clear();
		queueFamilies.resize(queueFamilyCount);
		vk.vkGetPhysicalDeviceQueueFamilyProperties(deviceHandles[i], &queueFamilyCount, &queueFamilies[0]);

		VULKAN_LOG.println("Adding device to list");
		this->physical_devices.push_back(VulkanPhysicalDevice(deviceHandles[i], deviceProperties, deviceFeatures, queueFamilies));
	}

	VULKAN_LOG.println("Successfully initialized VulkanInstance");
}

VulkanInstance::VulkanInstance() : handle(VK_NULL_HANDLE), surface(VK_NULL_HANDLE) {}

VulkanInstance::VulkanInstance(VulkanInstance &&instance) 
	: handle(instance.handle), surface(instance.surface), vk(instance.vk), physical_devices(instance.physical_devices)
{
	instance.handle = VK_NULL_HANDLE;
	instance.surface = VK_NULL_HANDLE;
	instance.physical_devices.clear();
}

VulkanInstance& VulkanInstance::operator=(VulkanInstance &&instance)
{
	this->handle = instance.handle;
	instance.handle = VK_NULL_HANDLE;

	this->surface = instance.surface;
	instance.surface = VK_NULL_HANDLE;

	this->physical_devices = instance.physical_devices;
	instance.physical_devices.clear();

	this->vk = instance.vk;

	return *this;
}


VulkanInstance::~VulkanInstance()
{
	destroy();
}

VkInstance VulkanInstance::getInstance() const
{
	return this->handle;
}


std::vector<VulkanPhysicalDevice> VulkanInstance::getPhysicalDevices() const
{
	return physical_devices;
}

void VulkanInstance::destroy()
{
	if (surface != VK_NULL_HANDLE) vk.vkDestroySurfaceKHR(handle, surface, NULL);
	if (handle != VK_NULL_HANDLE) vk.vkDestroyInstance(handle, NULL);
}