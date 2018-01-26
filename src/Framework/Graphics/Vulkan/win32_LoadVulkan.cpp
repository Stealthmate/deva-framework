#include "Config.hpp"

using namespace DevaFramework;
using Vulkan::LOG_VULKAN;

#ifdef DEVA_OS_WIN32

namespace
{
	HMODULE VULKAN = NULL;
	const char* VULKAN_DLL = "vulkan-1.dll";

}

void internal::loadVulkanOS(const std::string & path)
{
	std::string dllpath = path + VULKAN_DLL;
	VULKAN = LoadLibrary(dllpath.c_str());
	if (!VULKAN)
		throw DevaExternalFailureException(
			"Windows/Vulkan",
			"Could not load Vulkan dll");

	LOG_VULKAN.v("Load dll - SUCCESS");
	
	vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)GetProcAddress(VULKAN, "vkGetInstanceProcAddr");
	if(!vkGetInstanceProcAddr)
		throw DevaExternalFailureException(
			"Windows/Vulkan",
			"Could not load Vulkan function loader");
	else LOG_VULKAN.v("Load Vulkan function loader - SUCCESS");
}
#endif //DEVA_OS_WIN32
