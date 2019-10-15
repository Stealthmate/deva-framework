#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_CONFIG_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_CONFIG_HPP

#include "../Config.hpp"

#define VK_NO_PROTOTYPES

#ifdef DEVA_OS_WIN32
#define VK_USE_PLATFORM_WIN32_KHR
#endif
#ifdef DEVA_OS_LINUX
#define VK_USE_PLATFORM_XLIB_KHR
#endif

#include <vulkan/vulkan.h>

namespace DevaFramework
{
	namespace internal
	{

		extern PFN_vkGetInstanceProcAddr                           vkGetInstanceProcAddr;
		extern PFN_vkCreateInstance                                vkCreateInstance;
		extern PFN_vkEnumerateInstanceExtensionProperties          vkEnumerateInstanceExtensionProperties;
		extern PFN_vkEnumerateInstanceLayerProperties              vkEnumerateInstanceLayerProperties;

		void loadVulkanOS(const std::string &path = "");
		void getVulkanGlobalFunctions();
	}

	namespace Vulkan {
		DEVA_FRAMEWORK_API extern DevaLogger LOG_VULKAN;
		DEVA_FRAMEWORK_API void LoadVulkan(const std::string &dllpath = "");
		DEVA_FRAMEWORK_API bool instanceExtensionAvailable(const std::string & extensionName);
	}

}

#endif //DEVA_FRAMEWORK_GRAPHICS_VULKAN_CONFIG_HPP
