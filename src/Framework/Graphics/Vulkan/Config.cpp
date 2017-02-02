#include "Config.hpp"

#include "../../Exceptions.hpp"
#include "../../DevaLogger.hpp"

#include <vector>

using namespace DevaFramework;

PFN_vkGetInstanceProcAddr                           DevaFramework::internal::vkGetInstanceProcAddr = nullptr;

PFN_vkCreateInstance                                DevaFramework::internal::vkCreateInstance = nullptr;
PFN_vkEnumerateInstanceLayerProperties              DevaFramework::internal::vkEnumerateInstanceLayerProperties = nullptr;
PFN_vkEnumerateInstanceExtensionProperties          DevaFramework::internal::vkEnumerateInstanceExtensionProperties = nullptr;

DevaLogger DevaFramework::VULKAN_VERBOSE = DevaLogger("[Vulkan] Verbose: ", DevaLogger::LogLevel::LOG_MESSAGE, true);
DevaLogger DevaFramework::VULKAN_LOG = DevaLogger("[Vulkan] Log: ", DevaLogger::LogLevel::LOG_MESSAGE, true);
DevaLogger DevaFramework::VULKAN_WARN = DevaLogger("[Vulkan] Warning: ", DevaLogger::LogLevel::LOG_WARNING, true);
DevaLogger DevaFramework::VULKAN_ERR = DevaLogger("[Vulkan] Error: ", DevaLogger::LogLevel::LOG_ERROR, true);

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
	std::string msg = "Getting PFN "; \
	msg += #PFNNAME; \
	msg.append(70 - msg.length(), ' '); \
	VULKAN_VERBOSE.println(msg + " - SUCCESS"); \
}

void internal::getVulkanGlobalFunctions()
{
	LOADPFN(vkCreateInstance);
	LOADPFN(vkEnumerateInstanceExtensionProperties);
	LOADPFN(vkEnumerateInstanceLayerProperties);
	VULKAN_VERBOSE.println("Successfully got all global functions.");
}

#undef LOADPFN

void DevaFramework::LoadVulkan(const std::string &dllpath)
{
	internal::loadVulkanOS(dllpath);
	internal::getVulkanGlobalFunctions();

	uint32_t extension_count = 0;
	internal::vkEnumerateInstanceExtensionProperties(NULL, &extension_count, NULL);
	EXTENSIONS_AVAILABLE = std::vector<VkExtensionProperties>(extension_count);
	internal::vkEnumerateInstanceExtensionProperties(NULL, &extension_count, EXTENSIONS_AVAILABLE.data());

	VULKAN_VERBOSE.println("Successfully enumerated extensions");
}

bool DevaFramework::vulkanInstanceExtensionAvailable(const std::string & extensionName)
{
	VULKAN_VERBOSE << VULKAN_VERBOSE.stamp() << "Querying instance extension " + extensionName << "...";
	for (auto &i : EXTENSIONS_AVAILABLE)
	{
		if (extensionName == i.extensionName) 
		{
			VULKAN_VERBOSE << " FOUND" << Logger::endl;
			return true;
		}
	}
	VULKAN_VERBOSE << " NOT FOUND" << Logger::endl;
	return false;
}