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
		0                                   //apiVersion
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

	this->instance = VulkanInstance::create(INSTANCE_CREATE_INFO);
	auto vk = instance.getFunctionSet();
	auto pdevs = instance.getPhysicalDevices();

	std::vector<float> priorities = { 1.0f };

	for (auto &i : pdevs)
	{
		for (int q = 0; q <= i.queueFamilies.size() - 1; q++)
		{
			if (i.queueFamilies[q].queueFlags & VK_QUEUE_GRAPHICS_BIT)
			{
				VkDeviceQueueCreateInfo q_cinfo =
				{
					VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
					nullptr,
					0,
					q,
					static_cast<uint32_t>(priorities.size()),
					priorities.data()
				};

				VkDeviceCreateInfo dev_cinfo = 
				{
					VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
					nullptr,
					0,
					1,
					&q_cinfo,
					0,
					nullptr,
					0,
					nullptr,
					nullptr
				};

				VkDevice dev;
				vk.vkCreateDevice(i.handle, &dev_cinfo, nullptr, &dev);
				this->main_device = VulkanDevice(dev, instance);
				goto end_seek_device; //exits double loop
			}
		}
	}

	end_seek_device:
	;
}

void VulkanRenderer::renderExample()
{

}