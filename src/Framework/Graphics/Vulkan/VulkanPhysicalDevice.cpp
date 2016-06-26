#include "VulkanPhysicalDevice.hpp"

#include "../../Exceptions.hpp"

#include <iomanip>


using namespace DevaFramework;

namespace
{
	VkPhysicalDeviceProperties DEFAULT_PROPERTIES()
	{
		VkPhysicalDeviceProperties prop;
		memset(&prop, 0, sizeof(prop));
		return prop;
	}

	VkPhysicalDeviceFeatures DEFAULT_FEATURES()
	{
		VkPhysicalDeviceFeatures feat;
		memset(&feat, 0, sizeof(feat));
		return feat;
	}
}

VulkanPhysicalDevice::VulkanPhysicalDevice() : properties(DEFAULT_PROPERTIES()), features(DEFAULT_FEATURES()), handle(0)
{}

VulkanPhysicalDevice::VulkanPhysicalDevice(
	const VkPhysicalDevice &handle,
	const VkPhysicalDeviceProperties &properties, 
	const VkPhysicalDeviceFeatures&features,
	const std::vector<VkQueueFamilyProperties> &queueFamilies)
	: handle(handle), properties(properties), features(features), queueFamilies(queueFamilies) {}

const VkPhysicalDevice VulkanPhysicalDevice::getHandle() const
{
	return handle;
}

const VkPhysicalDeviceProperties VulkanPhysicalDevice::getProperties() const
{
	return properties;
}
const VkPhysicalDeviceFeatures VulkanPhysicalDevice::getFeatures() const
{
	return features;
}

size_t DevaFramework::VulkanPhysicalDevice::getQueueFamiliyCount() const
{
	return queueFamilies.size();
}

const VkQueueFamilyProperties & DevaFramework::VulkanPhysicalDevice::getQueueFamiliy(int i) const
{
	if (i >= queueFamilies.size()) throw DevaInvalidInputException("Invalid index");
	return queueFamilies[i];
}



namespace
{
	std::string parseVKVersion(uint32_t version)
	{
		return ""
			+ strm(VK_VERSION_MAJOR(version)) + "."
			+ strm(VK_VERSION_MINOR(version)) + "."
			+ strm(VK_VERSION_PATCH(version));
	}
	std::string parseDeviceType(VkPhysicalDeviceType type)
	{
		switch (type)
		{
		case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU: return "Integrated GPU";
		case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU: return "Discrete GPU";
		case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU: return "Virtual GPU";
		case VK_PHYSICAL_DEVICE_TYPE_CPU: return "CPU";
		case VK_PHYSICAL_DEVICE_TYPE_OTHER: return "Other";
		}

		return "Error parsing device type " + strm(type);
	}

	std::string parseQueueFamilyProperties(const VkQueueFamilyProperties &queueprop)
	{
		std::string str = "\tDevice queue familiy:";
		str += "\n\t\tSupported operations:      ";

		if (queueprop.queueFlags & VK_QUEUE_GRAPHICS_BIT) str += " Graphics";
		if (queueprop.queueFlags & VK_QUEUE_COMPUTE_BIT)  str += " Compute";
		if (queueprop.queueFlags & VK_QUEUE_TRANSFER_BIT)  str += " Transfer";
		if (queueprop.queueFlags & VK_QUEUE_SPARSE_BINDING_BIT)  str += " SparseBinding";

		str += "\n\t\tNumber of queues:           " + strm(queueprop.queueCount);

		//TODO: Implement additional property info

		return str;
	}
}

/*
VkQueueFlags    queueFlags;
uint32_t        queueCount;
uint32_t        timestampValidBits;
VkExtent3D      minImageTransferGranularity;
*/

/*

uint32_t                            apiVersion;
uint32_t                            driverVersion;
uint32_t                            vendorID;
uint32_t                            deviceID;
VkPhysicalDeviceType                deviceType;
char                                deviceName[VK_MAX_PHYSICAL_DEVICE_NAME_SIZE];
uint8_t                             pipelineCacheUUID[VK_UUID_SIZE];
VkPhysicalDeviceLimits              limits;
VkPhysicalDeviceSparseProperties    sparseProperties;
*/

std::string VulkanPhysicalDevice::to_string() const
{
	std::stringstream strs;
	strs << "\nVulkan Physical Device:";
	strs << "\n\tSupported API:         " << parseVKVersion(properties.apiVersion);
	strs << "\n\tDriver Version:        " << properties.driverVersion;
	strs << "\n\tVendor ID:             " << properties.vendorID;
	strs << "\n\tDevice ID:             " << properties.deviceID;
	strs << "\n\tDevice Type:           " << parseDeviceType(properties.deviceType);
	strs << "\n\tDevice Name:           " << properties.deviceName;

	//TODO: Implement pipelineCacheUUID, limits and sparse properties

	for (auto &i : queueFamilies) strs << "\n" << parseQueueFamilyProperties(i);

	strs << "\n";
	return strs.str();
}