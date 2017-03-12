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
			str += "\t" + std::string(ex.extensionName) + " - " + strm(major) + "." + strm(minor) + "." + strm(patch) + "\n";
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

			str += "\t" + name + "\n\t\tSpec Version: " + strm(specMajor) + "." + strm(specMinor) + "." + strm(specPatch) + "\n";
			str += "\t\tImpl Version: " + strm(implMajor) + "." + strm(implMinor) + "." + strm(implPatch) + "\n";
			str += "\t\t" + desc + "\n";
		}

		return str;
	}
}

VulkanPhysicalDeviceTraits VulkanPhysicalDeviceTraits::forDevice(const VulkanInstance &vkInstance, VkPhysicalDevice handle)
{
	auto & vk = vkInstance.vk();
	VulkanPhysicalDeviceTraits pdev;
	pdev.mHandle = handle;

	VkResult result;
	vk.vkGetPhysicalDeviceProperties(pdev.mHandle, &pdev.mProperties);
	vk.vkGetPhysicalDeviceFeatures(pdev.mHandle, &pdev.mFeatures);

	uint32_t queueFamilyCount = 0;
	vk.vkGetPhysicalDeviceQueueFamilyProperties(pdev.mHandle, &queueFamilyCount, NULL);

	pdev.mQueueFamilyProperties.clear();
	pdev.mQueueFamilyProperties.resize(queueFamilyCount);
	vk.vkGetPhysicalDeviceQueueFamilyProperties(pdev.mHandle, &queueFamilyCount, pdev.mQueueFamilyProperties.data());

	uint32_t ext_count = 0;
	result = vk.vkEnumerateDeviceExtensionProperties(pdev.mHandle, NULL, &ext_count, NULL);
	if (result != VK_SUCCESS)
		throw DevaException("Could not enumerate device extension properties");
	pdev.mExtensionProperties.clear();
	pdev.mExtensionProperties.resize(ext_count);
	result = vk.vkEnumerateDeviceExtensionProperties(pdev.mHandle, NULL, &ext_count, pdev.mExtensionProperties.data());
	if (result != VK_SUCCESS)
		throw DevaException("Could not populate device extensions vector");

	uint32_t layer_count = 0;
	result = vk.vkEnumerateDeviceLayerProperties(pdev.mHandle, &layer_count, NULL);
	if (result != VK_SUCCESS)
		throw DevaException("Could not enumerate device layer properties");
	pdev.mLayerProperties.clear();
	pdev.mLayerProperties.resize(layer_count);
	result = vk.vkEnumerateDeviceLayerProperties(pdev.mHandle, &layer_count, pdev.mLayerProperties.data());
	if (result != VK_SUCCESS)
		throw DevaException("Could not populate device layer properties");

	vk.vkGetPhysicalDeviceMemoryProperties(pdev.mHandle, &pdev.mMemoryProperties);

	return pdev;
}

VulkanPhysicalDeviceTraits::VulkanPhysicalDeviceTraits()
	:mHandle(VK_NULL_HANDLE) {}
VulkanPhysicalDeviceTraits::VulkanPhysicalDeviceTraits(const VulkanPhysicalDeviceTraits &pdev) = default;
VulkanPhysicalDeviceTraits::VulkanPhysicalDeviceTraits(VulkanPhysicalDeviceTraits &&pdev) = default;
VulkanPhysicalDeviceTraits& VulkanPhysicalDeviceTraits::operator=(const VulkanPhysicalDeviceTraits &pdev) = default;
VulkanPhysicalDeviceTraits& VulkanPhysicalDeviceTraits::operator=(VulkanPhysicalDeviceTraits &&pdev) = default;
VulkanPhysicalDeviceTraits::~VulkanPhysicalDeviceTraits() = default;

std::string VulkanPhysicalDeviceTraits::to_string() const
{
	std::stringstream strs;
	strs << "Vulkan Physical Device:";
	strs << "\n\tSupported API:         " << parseVKVersion(mProperties.apiVersion);
	strs << "\n\tDriver Version:        " << mProperties.driverVersion;
	strs << "\n\tVendor ID:             " << mProperties.vendorID;
	strs << "\n\tDevice ID:             " << mProperties.deviceID;
	strs << "\n\tDevice Type:           " << parseDeviceType(mProperties.deviceType);
	strs << "\n\tDevice Name:           " << mProperties.deviceName;

	//TODO: Implement pipelineCacheUUID, limits and sparse properties

	for (auto &i : mQueueFamilyProperties) strs << "\n" << parseQueueFamilyProperties(i);

	strs << "\n" << parseFeatures(mFeatures);
	strs << "\n" << parseExtensions(mExtensionProperties);
	strs << "\n" << parseLayers(mLayerProperties);

	strs << "\n";
	return strs.str();
}

VulkanPhysicalDeviceTraits::SurfaceProperties VulkanPhysicalDeviceTraits::getSurfaceProperties(const VulkanInstance &vkInstance, VkSurfaceKHR surface) const
{
	SurfaceProperties prop;
	auto &vk = vkInstance.vk();

	uint32_t formatCount;
	if (vk.vkGetPhysicalDeviceSurfaceFormatsKHR(mHandle, surface, &formatCount, NULL) != VK_SUCCESS)
		throw DevaExternalFailureException("Vulkan", "Error getting color formats!");
	prop.formats.resize(formatCount);
	if (vk.vkGetPhysicalDeviceSurfaceFormatsKHR(mHandle, surface, &formatCount, prop.formats.data()) != VK_SUCCESS)
		throw DevaExternalFailureException("Vulkan", "Device has no surface formats!");

	DevaExternalFailureException e = DevaExternalFailureException("Vulkan", "Vulkan error");

	VkSurfaceCapabilitiesKHR caps = {};
	if (vk.vkGetPhysicalDeviceSurfaceCapabilitiesKHR(mHandle, surface, &caps) != VK_SUCCESS) throw e;
	prop.capabilities = caps;

	uint32_t presentModeCount = 0;
	if (vk.vkGetPhysicalDeviceSurfacePresentModesKHR(mHandle, surface, &presentModeCount, NULL) != VK_SUCCESS) throw e;

	if (presentModeCount < 1) throw e;

	prop.presentModes.resize(presentModeCount);
	if (vk.vkGetPhysicalDeviceSurfacePresentModesKHR(mHandle, surface, &presentModeCount, prop.presentModes.data()) != VK_SUCCESS) throw e;

	return prop;
}