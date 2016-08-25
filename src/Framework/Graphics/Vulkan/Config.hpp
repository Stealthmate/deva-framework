#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_CONFIG_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_CONFIG_HPP

#include "../Config.hpp"
#include "../../DevaLogger.hpp"


#define VK_NO_PROTOTYPES

#ifdef DEVA_OS_WIN32
#define VK_USE_PLATFORM_WIN32_KHR
#endif

#include <vulkan/vulkan.h>

extern PFN_vkGetInstanceProcAddr                           vkGetInstanceProcAddr;
extern PFN_vkCreateInstance                                vkCreateInstance;
extern PFN_vkEnumerateInstanceExtensionProperties          vkEnumerateInstanceExtensionProperties;
extern PFN_vkEnumerateInstanceLayerProperties              vkEnumerateInstanceLayerProperties;

namespace DevaFramework
{
	namespace internal
	{
		void loadVulkanOS(const std::string &path = "");
		void getVulkanGlobalFunctions();
	}

	DEVA_FRAMEWORK_API extern DevaLogger VULKAN_LOG;
	DEVA_FRAMEWORK_API void LoadVulkan(const std::string &dllpath = "");
	DEVA_FRAMEWORK_API bool vulkanExtensionAvailable(const std::string & extensionName);
}

#endif //DEVA_FRAMEWORK_GRAPHICS_VULKAN_CONFIG_HPP