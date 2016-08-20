#include "Config.hpp"

#include "../../Exceptions.hpp"
#include "../../DevaLogger.hpp"

using namespace DevaFramework;

::PFN_vkCreateInstance                                vkCreateInstance = NULL;
::PFN_vkDestroyInstance                               vkDestroyInstance = NULL;

::PFN_vkCreateDevice                                  vkCreateDevice = NULL;
::PFN_vkDestroyDevice                                 vkDestroyDevice = NULL;

::PFN_vkGetInstanceProcAddr                           vkGetInstanceProcAddr = NULL;
::PFN_vkGetDeviceProcAddr                             vkGetDeviceProcAddr = NULL;

::PFN_vkEnumeratePhysicalDevices                      vkEnumeratePhysicalDevices = NULL;
::PFN_vkGetPhysicalDeviceFeatures                     vkGetPhysicalDeviceFeatures = NULL;
::PFN_vkGetPhysicalDeviceProperties                   vkGetPhysicalDeviceProperties = NULL;

::PFN_vkGetPhysicalDeviceQueueFamilyProperties        vkGetPhysicalDeviceQueueFamilyProperties = NULL;

#ifdef VK_USE_PLATFORM_WIN32_KHR		                   
::PFN_vkCreateWin32SurfaceKHR                         vkCreateWin32SurfaceKHR = NULL;
::PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR  vkGetPhysicalDeviceWin32PresentationSupportKHR = NULL;
#endif

::PFN_vkDestroySurfaceKHR                             vkDestroySurfaceKHR = NULL;


DevaLogger DevaFramework::VULKAN_LOG = DevaLogger("[Vulkan] Log: ", DevaLogger::LogLevel::LOG_MESSAGE, true);

namespace
{
	HMODULE VULKAN = NULL;
	const char* VULKAN_DLL = "vulkan-1.dll";
}

#define CHECK(a) \
if(!a) \
	throw new DevaExternalFailureException("Could not get PFN " #a, "DevaFramework::LoadVulkan", "GetProcAddress", "Windows/Vulkan"); \
else \
{ \
	std::string msg = "Load PFN "; \
	msg += #a; \
	msg.append(70 - msg.length(), ' '); \
	VULKAN_LOG.println(msg + " - SUCCESS"); \
}

void DevaFramework::LoadVulkan(const std::string &dllpath)
{
	std::string path = dllpath + VULKAN_DLL;
	VULKAN = LoadLibrary(path.c_str());
	if (!VULKAN)
		throw new DevaExternalFailureException(
			"Could not load Vulkan dll",
			"LoadLibrary(\"vulkan-1.dll\")",
			"DevaFramework::LoadVulkan(const std::string &dllpath)",
			"Windows/Vulkan");
	
	VULKAN_LOG.println("Load dll - SUCCESS");

	vkCreateInstance = (PFN_vkCreateInstance)GetProcAddress(VULKAN, "vkCreateInstance");
	CHECK(vkCreateInstance);
	vkDestroyInstance = (PFN_vkDestroyInstance)GetProcAddress(VULKAN, "vkDestroyInstance");
	CHECK(vkDestroyInstance);

	vkCreateDevice = (PFN_vkCreateDevice)GetProcAddress(VULKAN, "vkCreateDevice");
	CHECK(vkCreateDevice);
	vkDestroyDevice = (PFN_vkDestroyDevice)GetProcAddress(VULKAN, "vkDestroyDevice");
	CHECK(vkDestroyDevice);

	vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)GetProcAddress(VULKAN, "vkGetInstanceProcAddr");
	CHECK(vkGetInstanceProcAddr);
	vkGetDeviceProcAddr = (PFN_vkGetDeviceProcAddr)GetProcAddress(VULKAN, "vkGetDeviceProcAddr");
	CHECK(vkGetDeviceProcAddr);

	vkEnumeratePhysicalDevices = (PFN_vkEnumeratePhysicalDevices)GetProcAddress(VULKAN, "vkEnumeratePhysicalDevices");
	CHECK(vkEnumeratePhysicalDevices);
	vkGetPhysicalDeviceFeatures = (PFN_vkGetPhysicalDeviceFeatures)GetProcAddress(VULKAN, "vkGetPhysicalDeviceFeatures");
	CHECK(vkGetPhysicalDeviceFeatures);
	vkGetPhysicalDeviceProperties = (PFN_vkGetPhysicalDeviceProperties)GetProcAddress(VULKAN, "vkGetPhysicalDeviceProperties");
	CHECK(vkGetPhysicalDeviceProperties);

	vkGetPhysicalDeviceQueueFamilyProperties
		= (PFN_vkGetPhysicalDeviceQueueFamilyProperties)GetProcAddress(VULKAN, "vkGetPhysicalDeviceQueueFamilyProperties");
	CHECK(vkGetPhysicalDeviceQueueFamilyProperties);

#ifdef VK_USE_PLATFORM_WIN32_KHR		                   
	vkCreateWin32SurfaceKHR = (PFN_vkCreateWin32SurfaceKHR)GetProcAddress(VULKAN, "vkCreateWin32SurfaceKHR");
	CHECK(vkCreateWin32SurfaceKHR);
	vkGetPhysicalDeviceWin32PresentationSupportKHR
		= (PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR)GetProcAddress(VULKAN, "vkGetPhysicalDeviceWin32PresentationSupportKHR");
	CHECK(vkGetPhysicalDeviceWin32PresentationSupportKHR);
#endif

	vkDestroySurfaceKHR = (PFN_vkDestroySurfaceKHR)GetProcAddress(VULKAN, "vkDestroySurfaceKHR");
	CHECK(vkDestroySurfaceKHR);

	VULKAN_LOG.println("Loaded all functions successfully");
}