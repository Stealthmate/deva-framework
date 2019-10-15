#include "Config.hpp"

#include <vector>

using namespace DevaFramework;
using Vulkan::LOG_VULKAN;

PFN_vkGetInstanceProcAddr                           DevaFramework::internal::vkGetInstanceProcAddr = nullptr;

PFN_vkCreateInstance                                DevaFramework::internal::vkCreateInstance = nullptr;
PFN_vkEnumerateInstanceLayerProperties              DevaFramework::internal::vkEnumerateInstanceLayerProperties = nullptr;
PFN_vkEnumerateInstanceExtensionProperties          DevaFramework::internal::vkEnumerateInstanceExtensionProperties = nullptr;

DevaLogger Vulkan::LOG_VULKAN = DevaLogger("[Vulkan]: ");

namespace
{
	std::vector<VkExtensionProperties> EXTENSIONS_AVAILABLE;
}

#define LOADPFN(PFNNAME) \
PFNNAME = (PFN_##PFNNAME)vkGetInstanceProcAddr(nullptr, #PFNNAME); \
if(!PFNNAME) \
	throw DevaExternalFailureException("Windows/Vulkan", "Could not get PFN_"#PFNNAME); \
else \
{ \
	std::string msg = "Getting PFN "; \
	msg += #PFNNAME; \
	msg.append(70 - msg.length(), ' '); \
	LOG_VULKAN.v(msg + " - SUCCESS"); \
}

void internal::getVulkanGlobalFunctions()
{
	LOADPFN(vkCreateInstance);
	LOADPFN(vkEnumerateInstanceExtensionProperties);
	LOADPFN(vkEnumerateInstanceLayerProperties);
	LOG_VULKAN.v("Successfully got all global functions.");
}

#undef LOADPFN

void Vulkan::LoadVulkan(const std::string &dllpath)
{
	internal::loadVulkanOS(dllpath);
	internal::getVulkanGlobalFunctions();

	uint32_t extension_count = 0;
	internal::vkEnumerateInstanceExtensionProperties(NULL, &extension_count, NULL);
	EXTENSIONS_AVAILABLE = std::vector<VkExtensionProperties>(extension_count);
	internal::vkEnumerateInstanceExtensionProperties(NULL, &extension_count, EXTENSIONS_AVAILABLE.data());

	LOG_VULKAN.v("Successfully enumerated extensions");
}

bool Vulkan::instanceExtensionAvailable(const std::string & extensionName)
{
	LOG_VULKAN.v("Querying instance extension " + extensionName + "...", false);
	for (auto &i : EXTENSIONS_AVAILABLE)
	{
		if (extensionName == i.extensionName) 
		{
			LOG_VULKAN.v(" FOUND");
			return true;
		}
	}
	LOG_VULKAN.v(" NOT FOUND");
	return false;
}