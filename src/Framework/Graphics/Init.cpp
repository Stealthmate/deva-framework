#include "Init.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H

#include "../DevaLogger.hpp"
#include "../Exceptions.hpp"


using namespace DevaFramework;

namespace
{
	int loadFreeType() {
		FT_Library ft;

		if (FT_Init_FreeType(&ft)) {
			DevaLogger::err.println("Could not load FreeType.");
			return -1;
		}

		return 0;
	}

	static VkApplicationInfo DEFAULT_APPLICATION_SETTINGS;

	VkInstanceCreateInfo make_default_instance_settings()
	{
		VkInstanceCreateInfo instanceInfo;

		// Filling out application description:
		// sType is mandatory
		DEFAULT_APPLICATION_SETTINGS.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		// pNext is mandatory
		DEFAULT_APPLICATION_SETTINGS.pNext = NULL;
		// The name of our application
		DEFAULT_APPLICATION_SETTINGS.pApplicationName = "Vulkan Application";
		// The name of the engine (e.g: Game engine name)
		DEFAULT_APPLICATION_SETTINGS.pEngineName = "Deva Engine";
		// The version of the engine
		DEFAULT_APPLICATION_SETTINGS.engineVersion = DEVA_VERSION;
		// The version of Vulkan we're using for this application
		DEFAULT_APPLICATION_SETTINGS.apiVersion = VK_MAKE_VERSION(1, 0, 13);

		// Filling out instance description:
		// sType is mandatory
		instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		// pNext is mandatory
		instanceInfo.pNext = NULL;
		// flags is mandatory
		instanceInfo.flags = 0;
		// The application info structure is then passed through the instance
		instanceInfo.pApplicationInfo = &DEFAULT_APPLICATION_SETTINGS;
		// Don't enable and layer
		instanceInfo.enabledLayerCount = 0;
		instanceInfo.ppEnabledLayerNames = NULL;
		// Don't enable any extensions
		instanceInfo.enabledExtensionCount = 0;
		instanceInfo.ppEnabledExtensionNames = NULL;

		return instanceInfo;
	}
}


int DevaFramework::DEVA_INIT_GRAPHICS(const VkInstanceCreateInfo &vulkan_info)
{
	if (loadFreeType() != 0) return -1;

	GraphicsState::initVulkan(vulkan_info);

	return 0;
}

VkInstanceCreateInfo GraphicsState::DEFAULT_INSTANCE_SETTINGS = make_default_instance_settings();
std::vector<VulkanPhysicalDevice> GraphicsState::available_physical_devices = std::vector<VulkanPhysicalDevice>(0);


void GraphicsState::initVulkan(const VkInstanceCreateInfo &vulkan_info)
{
	VkInstance instance_handle;

	auto result = vkCreateInstance(&vulkan_info, NULL, &instance_handle);
	if (result != VK_SUCCESS) {
		throw DevaFailureException(
			"Failed to initialize Vulkan.",
			"int DevaFramework::DEVA_INIT_GRAPHICS(const VkInstanceCreateInfo &vulkan_info)",
			"vkCreateInstance(&vulkan_info, NULL, &instance_handle)");
	}

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

		available_physical_devices.push_back(VulkanPhysicalDevice(deviceHandles[i], deviceProperties, deviceFeatures, queueFamilies));
	}
}

uint32_t DevaFramework::GraphicsState::getPhysicalDeviceCount()
{
	return available_physical_devices.size();
}

const VulkanPhysicalDevice& GraphicsState::getPhysicalDevice(uint32_t i)
{
	if (i >= available_physical_devices.size())
		throw DevaInvalidInputException("Invalid device id");

	return available_physical_devices[i];
}
