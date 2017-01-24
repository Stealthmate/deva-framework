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
if(features.##FNAME) str += "TRUE"; \
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
			str += "\t" + strm(ex.extensionName) + " - " + strm(major) + "." + strm(minor) + "." + strm(patch) + "\n";
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


VulkanPhysicalDevice::VulkanPhysicalDevice()
{
	this->handle = VK_NULL_HANDLE;
}
VulkanPhysicalDevice::VulkanPhysicalDevice(const VulkanPhysicalDevice &pdev) = default;
VulkanPhysicalDevice::VulkanPhysicalDevice(VulkanPhysicalDevice &&pdev) = default;

VulkanPhysicalDevice& VulkanPhysicalDevice::operator=(const VulkanPhysicalDevice &pdev) = default;
VulkanPhysicalDevice& VulkanPhysicalDevice::operator=(VulkanPhysicalDevice &&pdev) = default;

VulkanPhysicalDevice::~VulkanPhysicalDevice() = default;



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

/*



*/

std::string VulkanPhysicalDevice::to_string() const
{
	std::stringstream strs;
	strs << "Vulkan Physical Device:";
	strs << "\n\tSupported API:         " << parseVKVersion(properties.apiVersion);
	strs << "\n\tDriver Version:        " << properties.driverVersion;
	strs << "\n\tVendor ID:             " << properties.vendorID;
	strs << "\n\tDevice ID:             " << properties.deviceID;
	strs << "\n\tDevice Type:           " << parseDeviceType(properties.deviceType);
	strs << "\n\tDevice Name:           " << properties.deviceName;

	//TODO: Implement pipelineCacheUUID, limits and sparse properties

	for (auto &i : queueFamilies) strs << "\n" << parseQueueFamilyProperties(i);

	strs << "\n" << parseFeatures(features);
	strs << "\n" << parseExtensions(extensions);
	strs << "\n" << parseLayers(layers);

	strs << "\n";
	return strs.str();
}