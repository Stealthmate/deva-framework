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

#define ERRCHK if( result != VK_SUCCESS ) throw DevaException("DevaFramework::VulkanInstance failed because of Vulkan. Check logs for more info.");

VulkanInstance VulkanInstance::create()
{
	return create(DEFAULT_INSTANCE_CREATE_INFO);
}

VulkanInstance VulkanInstance::create(const VkInstanceCreateInfo &info)
{
	VULKAN_LOG.println("Creating VulkanInstance...");
	VkInstance instance_handle;

	if (!vkCreateInstance)
		throw DevaProgrammerErrorException(//l
			"Vulkan not initialized",
			"DevaFramework::loadVulkan() not called?",
			"Call DevaFramework::loadVulkan() before using the Vulkan wrappers",
			"-");

	std::vector<std::string> extensions;
	for (int i = 0;i <= info.enabledExtensionCount - 1;i++)
	{
		extensions.push_back(*(info.ppEnabledExtensionNames + i));
		if (!vulkanInstanceExtensionAvailable(extensions[i]))
			throw DevaException("Could not create VkInstance - extension " + extensions[i] + " not supported by system.");
	}

	VULKAN_LOG.println("Getting VkInstance mHandle...");
	auto result = vkCreateInstance(&info, NULL, &instance_handle);
	VULKAN_LOG.println(strm(instance_handle));
	ERRCHK;

	return VulkanInstance(instance_handle);
}

void VulkanInstance::populatePDeviceList()
{
	VkResult result;

	VULKAN_LOG.println("Enumerating physical devices (count)...");
	uint32_t device_count = 0;
	result = mVk.vkEnumeratePhysicalDevices(mHandle, &device_count, NULL);
	ERRCHK;

	if (device_count == 0) {
		throw DevaException(std::string("No physical devices available."));
	}

	VULKAN_LOG.println("System has " + strm(device_count) + " devices.");

	VULKAN_LOG.println("Enumerating physical devices (mHandles)...");
	std::vector<VkPhysicalDevice> deviceHandles(device_count);
	result = mVk.vkEnumeratePhysicalDevices(mHandle, &device_count, &deviceHandles[0]);
	ERRCHK;

	VkPhysicalDeviceProperties deviceProperties;
	VkPhysicalDeviceFeatures deviceFeatures;
	std::vector<VkQueueFamilyProperties> queueFamilies;
	std::vector<VkExtensionProperties> deviceExtensions;
	std::vector<VkLayerProperties> deviceLayers;
	for (uint32_t i = 0; i <= device_count - 1; i++)
	{

		VULKAN_LOG.println("Querying VkPhysicalDeviceProperties for device " + strm(i) + "...");
		mVk.vkGetPhysicalDeviceProperties(deviceHandles[i], &deviceProperties);
		VULKAN_LOG.println("Querying VkPhysicalDeviceFeatures for device " + strm(i) + "...");
		mVk.vkGetPhysicalDeviceFeatures(deviceHandles[i], &deviceFeatures);

		uint32_t queueFamilyCount = 0;
		VULKAN_LOG.println("Querying VkQueueFamilyProperties (count) for device " + strm(i) + "...");
		mVk.vkGetPhysicalDeviceQueueFamilyProperties(deviceHandles[i], &queueFamilyCount, NULL);
		VULKAN_LOG.println("Device " + strm(i) + " supports " + strm(queueFamilyCount) + " queues");

		VULKAN_LOG.println("Querying VkQueueFamilyProperties (handles) for device " + strm(i) + "...");
		queueFamilies.clear();
		queueFamilies.resize(queueFamilyCount);
		mVk.vkGetPhysicalDeviceQueueFamilyProperties(deviceHandles[i], &queueFamilyCount, &queueFamilies[0]);

		VULKAN_LOG.println("Querying VkExtensionProperties (count) for device " + strm(i) + "...");
		uint32_t ext_count = 0;
		mVk.vkEnumerateDeviceExtensionProperties(deviceHandles[i], NULL, &ext_count, NULL);
		deviceExtensions.clear();
		deviceExtensions.resize(ext_count);
		VULKAN_LOG.println("Querying VkExtensionProperties (handles) for device " + strm(i) + "...");
		mVk.vkEnumerateDeviceExtensionProperties(deviceHandles[i], NULL, &ext_count, deviceExtensions.data());

		VULKAN_LOG.println("Querying VkLayerProperties (count) for device " + strm(i) + "...");
		uint32_t layer_count = 0;
		mVk.vkEnumerateDeviceLayerProperties(deviceHandles[i], &layer_count, NULL);
		deviceLayers.clear();
		deviceLayers.resize(layer_count);
		VULKAN_LOG.println("Querying VkLayerProperties (handles) for device " + strm(i) + "...");
		mVk.vkEnumerateDeviceLayerProperties(deviceHandles[i], &layer_count, deviceLayers.data());

		VULKAN_LOG.println("Adding device to list");
		this->physical_devices.push_back(VulkanPhysicalDevice(deviceHandles[i], deviceProperties, deviceFeatures, queueFamilies, deviceExtensions, deviceLayers));
	}
}


VulkanInstance::VulkanInstance(VkInstance handle) : mHandle(handle)
{
	VULKAN_LOG.println("Loading instance-local functions...");
	mVk = VulkanInstanceFunctionSet::load(mHandle);

	populatePDeviceList();

	VULKAN_LOG.println("Successfully initialized VulkanInstance");
}

VulkanInstance::VulkanInstance() : mHandle(VK_NULL_HANDLE) {}

VulkanInstance::VulkanInstance(VulkanInstance &&instance) 
	: mHandle(instance.mHandle), mVk(instance.mVk), physical_devices(instance.physical_devices)
{
	instance.mHandle = VK_NULL_HANDLE;
	instance.physical_devices.clear();
}

VulkanInstance& VulkanInstance::operator=(VulkanInstance &&instance)
{
	this->mHandle = instance.mHandle;
	instance.mHandle = VK_NULL_HANDLE;

	this->physical_devices = instance.physical_devices;
	instance.physical_devices.clear();

	mVk = instance.mVk;

	return *this;
}


VulkanInstance::~VulkanInstance()
{
	destroy();
}

VkInstance VulkanInstance::handle() const
{
	return this->mHandle;
}

VulkanInstanceFunctionSet VulkanInstance::vk() const
{
	return mVk;
}

std::vector<VulkanPhysicalDevice> VulkanInstance::getPhysicalDevices() const
{
	return physical_devices;
}

void VulkanInstance::destroy()
{
	if (mHandle != VK_NULL_HANDLE) mVk.vkDestroyInstance(mHandle, NULL);
}