#include "VulkanPhysicalDevice.hpp"
#include "VulkanInstance.hpp"

#include <iomanip>
#include <cstring>

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

	std::string parseVKVersion(uint32_t version)
	{
		return ""
			+ strf(VK_VERSION_MAJOR(version)) + "."
			+ strf(VK_VERSION_MINOR(version)) + "."
			+ strf(VK_VERSION_PATCH(version));
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

		return "Error parsing device type " + strf(type);
	}

	std::string parseQueueFamilyProperties(const VkQueueFamilyProperties &queueprop)
	{
		std::string str = "\tDevice queue familiy:";
		str += "\n\t\tSupported operations:      ";

		if (queueprop.queueFlags & VK_QUEUE_GRAPHICS_BIT) str += " Graphics";
		if (queueprop.queueFlags & VK_QUEUE_COMPUTE_BIT)  str += " Compute";
		if (queueprop.queueFlags & VK_QUEUE_TRANSFER_BIT)  str += " Transfer";
		if (queueprop.queueFlags & VK_QUEUE_SPARSE_BINDING_BIT)  str += " SparseBinding";

		str += "\n\t\tNumber of queues:           " + strf(queueprop.queueCount);

		//TODO: Implement additional property mInfo

		return str;
	}

#define STRF(FNAME) feature = #FNAME; \
str += "\t" + feature; \
str.append(50 - feature.length(), ' '); \
str += " - "; \
if(features. FNAME) str += "TRUE"; \
else str += "FALSE"; \
str += "\n";

	std::string parseFeatures(const VkPhysicalDeviceFeatures &features)
	{
		std::string str = "\tSupported features:\n";
		std::string feature = "";
		STRF(robustBufferAccess);
		STRF(fullDrawIndexUint32);
		STRF(imageCubeArray);
		STRF(independentBlend);
		STRF(geometryShader);
		STRF(tessellationShader);
		STRF(sampleRateShading);
		STRF(dualSrcBlend);
		STRF(logicOp);
		STRF(multiDrawIndirect);
		STRF(drawIndirectFirstInstance);
		STRF(depthClamp);
		STRF(depthBiasClamp);
		STRF(fillModeNonSolid);
		STRF(depthBounds);
		STRF(wideLines);
		STRF(largePoints);
		STRF(alphaToOne);
		STRF(multiViewport);
		STRF(samplerAnisotropy);
		STRF(textureCompressionETC2);
		STRF(textureCompressionASTC_LDR);
		STRF(textureCompressionBC);
		STRF(occlusionQueryPrecise);
		STRF(pipelineStatisticsQuery);
		STRF(vertexPipelineStoresAndAtomics);
		STRF(fragmentStoresAndAtomics);
		STRF(shaderTessellationAndGeometryPointSize);
		STRF(shaderImageGatherExtended);
		STRF(shaderStorageImageExtendedFormats);
		STRF(shaderStorageImageMultisample);
		STRF(shaderStorageImageReadWithoutFormat);
		STRF(shaderStorageImageWriteWithoutFormat);
		STRF(shaderUniformBufferArrayDynamicIndexing);
		STRF(shaderSampledImageArrayDynamicIndexing);
		STRF(shaderStorageBufferArrayDynamicIndexing);
		STRF(shaderStorageImageArrayDynamicIndexing);
		STRF(shaderClipDistance);
		STRF(shaderCullDistance);
		STRF(shaderFloat64);
		STRF(shaderInt64);
		STRF(shaderInt16);
		STRF(shaderResourceResidency);
		STRF(shaderResourceMinLod);
		STRF(sparseBinding);
		STRF(sparseResidencyBuffer);
		STRF(sparseResidencyImage2D);
		STRF(sparseResidencyImage3D);
		STRF(sparseResidency2Samples);
		STRF(sparseResidency4Samples);
		STRF(sparseResidency8Samples);
		STRF(sparseResidency16Samples);
		STRF(sparseResidencyAliased);
		STRF(variableMultisampleRate);
		STRF(inheritedQueries);

		return str;
	}

#undef STRF

	std::string parseExtensions(const std::vector<VkExtensionProperties> &extensions)
	{
		std::string str = "Supported Extensions:\n";

		for (auto &ex : extensions)
		{
			int major = VK_VERSION_MAJOR(ex.specVersion);
			int minor = VK_VERSION_MINOR(ex.specVersion);
			int patch = VK_VERSION_PATCH(ex.specVersion);
			str += "\t" + std::string(ex.extensionName) + " - " + strf(major) + "." + strf(minor) + "." + strf(patch) + "\n";
		}
		return str;
	}


	std::string parseLayers(const std::vector<VkLayerProperties> &layers)
	{
		std::string str = "Supported Layers:\n";

		for (auto &l : layers)
		{
			std::string name = l.layerName;
			int specMajor = VK_VERSION_MAJOR(l.specVersion);
			int specMinor = VK_VERSION_MINOR(l.specVersion);
			int specPatch = VK_VERSION_PATCH(l.specVersion);

			int implMajor = VK_VERSION_MAJOR(l.implementationVersion);
			int implMinor = VK_VERSION_MINOR(l.implementationVersion);
			int implPatch = VK_VERSION_PATCH(l.implementationVersion);

			std::string desc = l.description;

			str += "\t" + name + "\n\t\tSpec Version: " + strf(specMajor) + "." + strf(specMinor) + "." + strf(specPatch) + "\n";
			str += "\t\tImpl Version: " + strf(implMajor) + "." + strf(implMinor) + "." + strf(implPatch) + "\n";
			str += "\t\t" + desc + "\n";
		}

		return str;
	}
}

VulkanPhysicalDevice Vulkan::getPhysicalDeviceStruct(const VulkanInstance &vkInstance, VkPhysicalDevice handle)
{
	auto & vk = vkInstance.vk;
	VulkanPhysicalDevice pdev;
	pdev.handle = handle;

	VkResult result;
	vk.vkGetPhysicalDeviceProperties(pdev.handle, &pdev.properties);
	vk.vkGetPhysicalDeviceFeatures(pdev.handle, &pdev.features);

	uint32_t queueFamilyCount = 0;
	vk.vkGetPhysicalDeviceQueueFamilyProperties(pdev.handle, &queueFamilyCount, NULL);

	pdev.queueFamilyProperties.clear();
	pdev.queueFamilyProperties.resize(queueFamilyCount);
	vk.vkGetPhysicalDeviceQueueFamilyProperties(pdev.handle, &queueFamilyCount, pdev.queueFamilyProperties.data());

	uint32_t ext_count = 0;
	result = vk.vkEnumerateDeviceExtensionProperties(pdev.handle, NULL, &ext_count, NULL);
	if (result != VK_SUCCESS)
		throw DevaException("Could not enumerate device extension properties");
	pdev.extensionProperties.clear();
	pdev.extensionProperties.resize(ext_count);
	result = vk.vkEnumerateDeviceExtensionProperties(pdev.handle, NULL, &ext_count, pdev.extensionProperties.data());
	if (result != VK_SUCCESS)
		throw DevaException("Could not populate device extensions vector");

	uint32_t layer_count = 0;
	result = vk.vkEnumerateDeviceLayerProperties(pdev.handle, &layer_count, NULL);
	if (result != VK_SUCCESS)
		throw DevaException("Could not enumerate device layer properties");
	pdev.layerProperties.clear();
	pdev.layerProperties.resize(layer_count);
	result = vk.vkEnumerateDeviceLayerProperties(pdev.handle, &layer_count, pdev.layerProperties.data());
	if (result != VK_SUCCESS)
		throw DevaException("Could not populate device layer properties");

	vk.vkGetPhysicalDeviceMemoryProperties(pdev.handle, &pdev.memoryProperties);

	return pdev;
}

std::string Vulkan::toString(const VulkanPhysicalDevice &pdev)
{
	std::stringstream strs;
	strs << "Vulkan Physical Device:";
	strs << "\n\tSupported API:         " << parseVKVersion(pdev.properties.apiVersion);
	strs << "\n\tDriver Version:        " << pdev.properties.driverVersion;
	strs << "\n\tVendor ID:             " << pdev.properties.vendorID;
	strs << "\n\tDevice ID:             " << pdev.properties.deviceID;
	strs << "\n\tDevice Type:           " << parseDeviceType(pdev.properties.deviceType);
	strs << "\n\tDevice Name:           " << pdev.properties.deviceName;

	//TODO: Implement pipelineCacheUUID, limits and sparse properties

	for (auto &i : pdev.queueFamilyProperties) strs << "\n" << parseQueueFamilyProperties(i);

	strs << "\n" << parseFeatures(pdev.features);
	strs << "\n" << parseExtensions(pdev.extensionProperties);
	strs << "\n" << parseLayers(pdev.layerProperties);

	strs << "\n";
	return strs.str();
}

Vulkan::PhysicalDeviceSurfaceProperties Vulkan::getSurfaceProperties(
	const VulkanInstance &vkInstance, 
	const VulkanPhysicalDevice &pdev, 
	VkSurfaceKHR surface)
{
	PhysicalDeviceSurfaceProperties prop;
	auto &vk = vkInstance.vk;

	uint32_t formatCount;
	if (vk.vkGetPhysicalDeviceSurfaceFormatsKHR(pdev.handle, surface, &formatCount, NULL) != VK_SUCCESS)
		throw DevaExternalFailureException("Vulkan", "Error getting color formats!");
	prop.formats.resize(formatCount);
	if (vk.vkGetPhysicalDeviceSurfaceFormatsKHR(pdev.handle, surface, &formatCount, prop.formats.data()) != VK_SUCCESS)
		throw DevaExternalFailureException("Vulkan", "Device has no surface formats!");

	DevaExternalFailureException e = DevaExternalFailureException("Vulkan", "Vulkan error");

	VkSurfaceCapabilitiesKHR caps = {};
	if (vk.vkGetPhysicalDeviceSurfaceCapabilitiesKHR(pdev.handle, surface, &caps) != VK_SUCCESS) throw e;
	prop.capabilities = caps;

	uint32_t presentModeCount = 0;
	if (vk.vkGetPhysicalDeviceSurfacePresentModesKHR(pdev.handle, surface, &presentModeCount, NULL) != VK_SUCCESS) throw e;

	if (presentModeCount < 1) throw e;

	prop.presentModes.resize(presentModeCount);
	if (vk.vkGetPhysicalDeviceSurfacePresentModesKHR(pdev.handle, surface, &presentModeCount, prop.presentModes.data()) != VK_SUCCESS) throw e;

	return prop;
}