#include "VulkanInstance.hpp"
#include "../../Exceptions.hpp"


using namespace DevaFramework;

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

VulkanInstance VulkanInstance::create()
{
	return create(DEFAULT_INSTANCE_CREATE_INFO);
}

VulkanInstance VulkanInstance::create(const VkInstanceCreateInfo &info)
{
	return VulkanInstance(info);
}

VulkanInstance::VulkanInstance(const VkInstanceCreateInfo &info)
{
	VkInstance instance_handle;

	auto result = vkCreateInstance(&info, NULL, &instance_handle);
	if (result != VK_SUCCESS) {
		throw DevaFailureException(
			"Failed to initialize Vulkan.",
			"int DevaFramework::DEVA_INIT_GRAPHICS(const VkInstanceCreateInfo &vulkan_info)",
			"vkCreateInstance(&vulkan_info, NULL, &instance_handle)");
	}

	this->handle = instance_handle;

	uint32_t device_count = 0;
	result = vkEnumeratePhysicalDevices(instance_handle, &device_count, NULL);
	if (result != VK_SUCCESS) {
		throw DevaFailureException(
			"Failed to get physical device count.",
			"int DevaFramework::DEVA_INIT_GRAPHICS(const VkInstanceCreateInfo &vulkan_info)",
			"vkEnumeratePhysicalDevices(instance_handle, &device_count, NULL)");
	}

	if (device_count == 0) {
		throw DevaException(
			"No physical devices available.");
	}

	// Get the physical device handles
	std::vector<VkPhysicalDevice> deviceHandles(device_count);
	result = vkEnumeratePhysicalDevices(instance_handle, &device_count, &deviceHandles[0]);
	if (result != VK_SUCCESS) {
		throw DevaFailureException(
			"Failed to get physical devices.",
			"int DevaFramework::DEVA_INIT_GRAPHICS(const VkInstanceCreateInfo &vulkan_info)",
			"vkEnumeratePhysicalDevices(instance_handle, &device_count, &physical_devices[0])");
	}

	// Enumerate all physical devices
	VkPhysicalDeviceProperties deviceProperties;
	VkPhysicalDeviceFeatures deviceFeatures;
	std::vector<VkQueueFamilyProperties> queueFamilies;
	for (uint32_t i = 0; i <= device_count - 1; i++) {

		vkGetPhysicalDeviceProperties(deviceHandles[i], &deviceProperties);
		vkGetPhysicalDeviceFeatures(deviceHandles[i], &deviceFeatures);

		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(deviceHandles[i], &queueFamilyCount, NULL);

		queueFamilies.clear();
		queueFamilies.resize(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(deviceHandles[i], &queueFamilyCount, &queueFamilies[0]);

		this->physical_devices.push_back(VulkanPhysicalDevice(deviceHandles[i], deviceProperties, deviceFeatures, queueFamilies));
	}
}

VkInstance VulkanInstance::getInstance() const
{
	return this->handle;
}