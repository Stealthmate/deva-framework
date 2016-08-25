#include "VulkanRenderer.hpp"

using namespace DevaFramework;
using namespace DevaEngine;

namespace
{
	const VkApplicationInfo APPLICATION_INFO =
	{
		VK_STRUCTURE_TYPE_APPLICATION_INFO, //sType
		NULL,                               //pNext
		"Test App",                         //pApplicationName
		VK_MAKE_VERSION(1, 0, 0),           //applicationVersion
		"Deva Engine",                      //pEngineName
		VK_MAKE_VERSION(1, 0, 0),           //engineVersion
		VK_MAKE_VERSION(1, 0, 13)           //apiVersion
	};

	size_t N_EXTENSIONS = 3;
	const char * EXTENSIONS[] =
	{
		"VK_KHR_surface",
		"VK_KHR_win32_surface",
		"VK_EXT_debug_report"
	};


	const VkInstanceCreateInfo INSTANCE_CREATE_INFO =
	{
		VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO, //sType
		NULL,                                   //pNext
		0,                                      //flags - must be 0 as per current spec (2016/08/21)
		&APPLICATION_INFO,                      //pApplicationInfo
		0,                                      //enabledLayerCount
		NULL,                                   //ppEnabledLayerNames
		N_EXTENSIONS,                           //enabledExtensionCount
		EXTENSIONS                              //ppEnabledExtensionNames
	};

	const bool VULKAN_LOADED = false;
}


VulkanRenderer::VulkanRenderer() : instance()
{
	if (!VULKAN_LOADED) LoadVulkan();

	for (int i = 0; i <= N_EXTENSIONS - 1;i++)
	{
		std::string extname = EXTENSIONS[i];
		if (!vulkanExtensionAvailable(extname))
		{
			throw DevaException("Vulkan extension " + extname + " not supported on system.");
		}
	}

	this->instance = VulkanInstance::create(INSTANCE_CREATE_INFO);
	DevaLogger::log.println(instance.getPhysicalDevices()[0].to_string());


}

void VulkanRenderer::renderExample()
{

}