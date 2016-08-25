#include "Config.hpp"

#ifdef DEVA_OS_WIN32

#include "../../Exceptions.hpp"
#include "../../DevaLogger.hpp"

namespace
{
	HMODULE VULKAN = NULL;
	const char* VULKAN_DLL = "vulkan-1.dll";

}

void DevaFramework::internal::loadVulkanOS(const std::string & path)
{
	std::string dllpath = path + VULKAN_DLL;
	VULKAN = LoadLibrary(dllpath.c_str());
	if (!VULKAN)
		throw DevaExternalFailureException(
			"Could not load Vulkan dll",
			"LoadLibrary(\"vulkan-1.dll\")",
			"DevaFramework::loadVulkanOS",
			"Windows/Vulkan");

	VULKAN_LOG.println("Load dll - SUCCESS");
	
	vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)GetProcAddress(VULKAN, "vkGetInstanceProcAddr");
	if(!vkGetInstanceProcAddr)
		throw DevaExternalFailureException(
			"Could not load Vulkan function loader",
			"LoadLibrary(\"vulkan-1.dll\")",
			"DevaFramework::loadVulkanOS",
			"Windows/Vulkan");
	else VULKAN_LOG.println("Load Vulkan function loader - SUCCESS");
}
#endif //DEVA_OS_WIN32