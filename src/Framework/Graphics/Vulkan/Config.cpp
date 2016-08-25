#include "Config.hpp"

#include "../../Exceptions.hpp"
#include "../../DevaLogger.hpp"

#include <vector>

using namespace DevaFramework;

PFN_vkGetInstanceProcAddr                           vkGetInstanceProcAddr = nullptr;

PFN_vkCreateInstance                                vkCreateInstance = nullptr;
PFN_vkEnumerateInstanceLayerProperties              vkEnumerateInstanceLayerProperties = nullptr;
PFN_vkEnumerateInstanceExtensionProperties          vkEnumerateInstanceExtensionProperties = nullptr;

DevaLogger DevaFramework::VULKAN_LOG = DevaLogger("[Vulkan] Log: ", DevaLogger::LogLevel::LOG_MESSAGE, true);

namespace
{
	std::vector<VkExtensionProperties> EXTENSIONS_AVAILABLE;
}

#define LOADPFN(PFNNAME) \
PFNNAME = (PFN_##PFNNAME)vkGetInstanceProcAddr(nullptr, #PFNNAME); \
if(!PFNNAME) \
	throw DevaExternalFailureException("Could not get PFN_"#PFNNAME, "DevaFramework::internal::getVulkanGlobalFunctions", "vkGetInstanceProcAddr", "Windows/Vulkan"); \
else \
{ \
	std::string msg = "Get PFN "; \
	msg += #PFNNAME; \
	msg.append(70 - msg.length(), ' '); \
	VULKAN_LOG.println(msg + " - SUCCESS"); \
}

void internal::getVulkanGlobalFunctions()
{
	LOADPFN(vkCreateInstance);
	LOADPFN(vkEnumerateInstanceExtensionProperties);
	LOADPFN(vkEnumerateInstanceLayerProperties);
	VULKAN_LOG.println("Successfully got all global functions.");
}

#undef LOADPFN

void DevaFramework::LoadVulkan(const std::string &dllpath)
{
	internal::loadVulkanOS(dllpath);
	internal::getVulkanGlobalFunctions();

	uint32_t extension_count = 0;
	vkEnumerateInstanceExtensionProperties(NULL, &extension_count, NULL);
	EXTENSIONS_AVAILABLE = std::vector<VkExtensionProperties>(extension_count);
	vkEnumerateInstanceExtensionProperties(NULL, &extension_count, EXTENSIONS_AVAILABLE.data());

	VULKAN_LOG.println("Successfully enumerated extensions");
}

bool DevaFramework::vulkanExtensionAvailable(const std::string & extensionName)
{
	VULKAN_LOG << "Querying extension " + extensionName << "...";
	for (auto &i : EXTENSIONS_AVAILABLE)
	{
		if (extensionName == i.extensionName) 
		{
			VULKAN_LOG << " FOUND" << Logger::endl;
			return true;
		}
	}
	VULKAN_LOG << " NOT FOUND" << Logger::endl;
	return false;
}