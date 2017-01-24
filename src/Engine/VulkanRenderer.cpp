#include "VulkanRenderer.hpp"

#include "VulkanPipelineBuilder.hpp"

#include <DevaFramework\Graphics\Vulkan\Common.hpp>

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
		VK_KHR_SURFACE_EXTENSION_NAME,
		VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
		VK_EXT_DEBUG_REPORT_EXTENSION_NAME
	};

	const char* INSTANCE_LAYERS[] =
	{
		"VK_LAYER_LUNARG_standard_validation"
	};

	const VkInstanceCreateInfo INSTANCE_CREATE_INFO =
	{
		VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,        //sType
		NULL,                                          //pNext
		0,                                             //flags - must be 0 as per current spec (2016/08/21)
		&APPLICATION_INFO,                             //pApplicationInfo
		sizeof INSTANCE_LAYERS / sizeof(const char*),  //enabledLayerCount
		INSTANCE_LAYERS,                               //ppEnabledLayerNames
		N_EXTENSIONS,                                  //enabledExtensionCount
		EXTENSIONS                                     //ppEnabledExtensionNames
	};

	const char * DEVICE_EXTENSIONS[] =
	{
		VK_KHR_SWAPCHAIN_EXTENSION_NAME,
		
	};

	const bool VULKAN_LOADED = false;

	VkSurfaceKHR createSurface(const VulkanInstance &instance, const Window &wnd)
	{
		auto os = wnd.getOSHandles();
		VkWin32SurfaceCreateInfoKHR surface_cinfo =
		{
			VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR,
			nullptr,
			0,
			(HINSTANCE)os->win32_hinstance(),
			(HWND)os->win32_hwnd()
		};

		VkSurfaceKHR surface;
		instance.getFunctionSet().vkCreateWin32SurfaceKHR(instance.getHandle(), &surface_cinfo, nullptr, &surface);
		return surface;
	}

	bool pickGPU(const VulkanInstance &instance, const VkSurfaceKHR &surface, VulkanPhysicalDevice * gpu, uint32_t * queueIndex)
	{
		VULKAN_LOG.toggle(true);
		VULKAN_LOG.println(instance.getPhysicalDevices()[0].to_string());

		auto vk = instance.getFunctionSet();
		auto pdevs = instance.getPhysicalDevices();
		for (auto &pdev : pdevs) {
			if (pdev.properties.deviceType != VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) continue;
			for (int i = 0;i < pdev.queueFamilies.size();i++)
			{
				auto& q = pdev.queueFamilies[i];
				if (q.queueFlags & VK_QUEUE_GRAPHICS_BIT == 0) continue;

				VkBool32 supportsPresent;
				vk.vkGetPhysicalDeviceSurfaceSupportKHR(pdev.handle,
					i,
					surface,
					&supportsPresent);
				if (supportsPresent == VK_TRUE) {
					*queueIndex = i;
					*gpu = pdev;
					return true;
				}
			}
		}
		return false;
	}

	VulkanDevice createLogicalDevice(const VulkanInstance& instance, const VulkanPhysicalDevice &pdev, uint32_t queueIndex)
	{
		std::vector<float> priorities = { 1.0f, 1.0f };
		VkDeviceQueueCreateInfo q_cinfo;
		q_cinfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		q_cinfo.pNext = nullptr;
		q_cinfo.queueCount = 2;
		q_cinfo.queueFamilyIndex = queueIndex;
		q_cinfo.pQueuePriorities = priorities.data();
		q_cinfo.flags = 0;

		for (auto ext : DEVICE_EXTENSIONS)
		{
			bool supported = false;
			for (auto &devext : pdev.extensions)
			{
				supported = std::string(devext.extensionName).compare(ext) == 0;
				if (supported) break;
			}
			if (!supported) throw DevaException("Cannot create VulkanDevice: Unsupported extension " + std::string(ext));
		}

		VkDeviceCreateInfo dev_cinfo =
		{
			VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,            // sType
			nullptr,                                         // pNext
			0,                                               // flags
			1,                                               // queueCreateInfoCount
			&q_cinfo,                                        // pQueueCreateInfos
			0,                                               // enabledLayerCount
			nullptr,                                         // ppEnabledLayerNames
			sizeof DEVICE_EXTENSIONS / sizeof(const char*),  // enabledExtensionCount
			DEVICE_EXTENSIONS,                               // enabledExtensionNames
			nullptr                                          // pEnabledFeatures
		};

		VkDevice dev;
		VkResult result = instance.getFunctionSet().vkCreateDevice(pdev.handle, &dev_cinfo, nullptr, &dev);
		if (result != VK_SUCCESS) throw DevaException("Could not create VkDevice: Vulkan error " + result);

		VulkanDevice vdev = VulkanDevice(dev, instance);

		return vdev;
	}
}


VulkanRenderer::VulkanRenderer() {}

VKAPI_ATTR VkBool32 VKAPI_CALL debug(
	VkDebugReportFlagsEXT       flags,
	VkDebugReportObjectTypeEXT  objectType,
	uint64_t                    object,
	size_t                      location,
	int32_t                     messageCode,
	const char*                 pLayerPrefix,
	const char*                 pMessage,
	void*                       pUserData)
{
	VULKAN_ERR << "Error from: " << pLayerPrefix << DevaLogger::endl;
	VULKAN_ERR << "Error: " << pMessage << DevaLogger::endl;
	return VK_FALSE;
}

VulkanRenderer::VulkanRenderer(const Window &wnd)
{
	if (!VULKAN_LOADED) LoadVulkan();

	VULKAN_LOG.toggle(false);
	this->instance = VulkanInstance::create(INSTANCE_CREATE_INFO);

	auto &vk = instance.getFunctionSet();
	/* Setup callback creation information */
	VkDebugReportCallbackCreateInfoEXT callbackCreateInfo;
	callbackCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CREATE_INFO_EXT;
	callbackCreateInfo.pNext = nullptr;
	callbackCreateInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT |VK_DEBUG_REPORT_WARNING_BIT_EXT | VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT;
	callbackCreateInfo.pfnCallback = &debug;
	callbackCreateInfo.pUserData = nullptr;

	/* Register the callback */
	VkDebugReportCallbackEXT callback;
	VkResult result = vk.vkCreateDebugReportCallbackEXT(instance.getHandle(), &callbackCreateInfo, nullptr, &callback);


	this->surface = ::createSurface(instance, wnd);
	VulkanPhysicalDevice gpu;
	uint32_t queueIndex = 0;
	if (!::pickGPU(instance, surface, &gpu, &queueIndex)) throw DevaException("Could not find suitable GPU and/or queue");

	this->main_pdev = gpu;
	this->main_device = ::createLogicalDevice(instance, gpu, queueIndex);

	VULKAN_LOG.toggle(true);
	attachToWindow(wnd, queueIndex);

	try {
		createPipeline();
	}
	catch (DevaException ex) {
		VULKAN_LOG.println("EXCEPTION MATE");
		VULKAN_ERR.println(ex.what());
	}
}

void VulkanRenderer::attachToWindow(const Window &wnd, uint32_t queueIndex)
{
	auto os = wnd.getOSHandles();

	VkWin32SurfaceCreateInfoKHR surface_cinfo =
	{
		VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR,
		nullptr,
		0,
		(HINSTANCE)os->win32_hinstance(),
		(HWND)os->win32_hwnd()
	};

	auto dev = instance.getPhysicalDevices()[0];
	auto vk = instance.getFunctionSet();

	vk.vkCreateWin32SurfaceKHR(instance.getHandle(), &surface_cinfo, nullptr, &this->surface);

	unsigned int queue = UINT_MAX;

	auto pdev_prop = dev.queueFamilies[0];

	for (uint32_t i = 0; i < dev.queueFamilies.size(); i++) {
		VkBool32 supportsPresent;
		VkBool32 supportsGraphics = dev.queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT != 0;
		vk.vkGetPhysicalDeviceSurfaceSupportKHR(dev.handle,
			i,
			surface,
			&supportsPresent);
		if (supportsPresent == VK_TRUE && supportsGraphics == VK_TRUE) {
			queue = i;
		}
	}

	if (queue == UINT_MAX)
		throw DevaExternalFailureException("No queues which support both presentation and graphics exist", "", "VulkanRenderer::attachToWindw", "Vulkan");

	this->renderQueue = queue;

	uint32_t formatCount;
	if (vk.vkGetPhysicalDeviceSurfaceFormatsKHR(dev.handle, surface, &formatCount, NULL) != VK_SUCCESS)
		throw DevaExternalFailureException("No color formats!", "vkGetPhysicalDeviceSurfaceFormatsKHR", "VulkanRenderer::attachToWindow", "Vulkan");

	if (formatCount == 0)
		throw DevaExternalFailureException("No color formats!", "vkGetPhysicalDeviceSurfaceFormatsKHR", "VulkanRenderer::attachToWindow", "Vulkan");
	std::vector<VkSurfaceFormatKHR> surfaceFormats(formatCount);

	if (vk.vkGetPhysicalDeviceSurfaceFormatsKHR(dev.handle, surface, &formatCount, &surfaceFormats[0]) != VK_SUCCESS)
		throw DevaExternalFailureException("No color formats!", "vkGetPhysicalDeviceSurfaceFormatsKHR", "VulkanRenderer::attachToWindow", "Vulkan");

	// If the format list includes just one entry of VK_FORMAT_UNDEFINED,
	// the surface has no preferred format. Otherwise, at least one
	// supported format will be returned

	if (formatCount == 1 && surfaceFormats[0].format == VK_FORMAT_UNDEFINED)
		this->colorFormat = VK_FORMAT_B8G8R8A8_UNORM;
	else {
		if (formatCount == 0)
			throw DevaExternalFailureException("No color formats!", "vkGetPhysicalDeviceSurfaceFormatsKHR", "VulkanRenderer::attachToWindow", "Vulkan");
		this->colorFormat = surfaceFormats[0].format;
	}
	this->colorSpace = surfaceFormats[0].colorSpace;

	DevaExternalFailureException e = DevaExternalFailureException("Vulkan error", "", "", "Vulkan");

	VkSurfaceCapabilitiesKHR caps = {};
	if (vk.vkGetPhysicalDeviceSurfaceCapabilitiesKHR(dev.handle, surface, &caps) != VK_SUCCESS) throw e;

	VkExtent2D swapchainExtent = {};

	if (caps.currentExtent.width == -1 || caps.currentExtent.height == -1) {
		swapchainExtent.width = wnd.getWidth();
		swapchainExtent.height = wnd.getHeight();
	}
	else {
		swapchainExtent = caps.currentExtent;
	}

	uint32_t presentModeCount = 0;
	if (vk.vkGetPhysicalDeviceSurfacePresentModesKHR(dev.handle, surface, &presentModeCount, NULL) != VK_SUCCESS) throw e;

	if (presentModeCount < 1) throw e;

	std::vector<VkPresentModeKHR> presentModes(presentModeCount);
	if (vk.vkGetPhysicalDeviceSurfacePresentModesKHR(dev.handle, surface, &presentModeCount, presentModes.data()) != VK_SUCCESS) throw e;

	VkPresentModeKHR presentMode = VK_PRESENT_MODE_FIFO_KHR;

	for (uint32_t i = 0; i < presentModeCount; i++) {
		if (presentModes[i] == VK_PRESENT_MODE_MAILBOX_KHR) {
			presentMode = VK_PRESENT_MODE_MAILBOX_KHR;
			break;
		}

		if (presentModes[i] == VK_PRESENT_MODE_IMMEDIATE_KHR)
			presentMode = VK_PRESENT_MODE_IMMEDIATE_KHR;
	}

	if (caps.maxImageCount < 1) throw e;

	uint32_t imageCount = caps.minImageCount + 1;
	if (imageCount > caps.maxImageCount) imageCount = caps.maxImageCount;

	uint32_t indices = {
		queueIndex
	};

	VkSwapchainCreateInfoKHR swapchainCreateInfo = {};
	swapchainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	swapchainCreateInfo.surface = surface;
	swapchainCreateInfo.minImageCount = imageCount;
	swapchainCreateInfo.imageFormat = colorFormat;
	swapchainCreateInfo.imageColorSpace = colorSpace;
	swapchainCreateInfo.imageExtent = swapchainExtent;
	swapchainCreateInfo.imageArrayLayers = 1;
	swapchainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	swapchainCreateInfo.queueFamilyIndexCount = 1;
	swapchainCreateInfo.pQueueFamilyIndices = &indices;
	swapchainCreateInfo.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
	swapchainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	swapchainCreateInfo.presentMode = presentMode;
	swapchainCreateInfo.oldSwapchain = VK_NULL_HANDLE;

	this->swapchain = VulkanSwapchain::createSwapchain(this->main_device, swapchainCreateInfo);

	VULKAN_LOG.println("Created swapchain");

	//TODO: Implement OS-specific code

}
VkRenderPass rpass;


VkSemaphore imageAvailableSemaphore;
VkSemaphore renderFinishedSemaphore;
std::vector<VkCommandBuffer> commandBuffers;

void VulkanRenderer::createPipeline()
{
	auto vert = vulkanShaderFromFile(this->main_device, "shaders/vert.spv");
	auto frag = vulkanShaderFromFile(this->main_device, "shaders/frag.spv");

	VulkanGraphicsPipelineBuilder plb;
	plb.attachShader(vert, VK_SHADER_STAGE_VERTEX_BIT, "main")
		.attachShader(frag, VK_SHADER_STAGE_FRAGMENT_BIT, "main")
		.outputExtent(swapchain.extent);
	auto &vk = main_device.getFunctionSet();
	auto device = main_device.getHandle();

	VULKAN_LOG.println("JESUS");

	VulkanDeleter<VkPipelineLayout> pipelineLayout{ device, vk.vkDestroyPipelineLayout };

	VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutInfo.setLayoutCount = 0; // Optional
	pipelineLayoutInfo.pSetLayouts = nullptr; // Optional
	pipelineLayoutInfo.pushConstantRangeCount = 0; // Optional
	pipelineLayoutInfo.pPushConstantRanges = 0; // Optional

	if (vk.vkCreatePipelineLayout(device, &pipelineLayoutInfo, nullptr,
		pipelineLayout.replace()) != VK_SUCCESS) {
		throw DevaException("Failed to create pipeline layout!");
	}

	VkAttachmentDescription colorAttachment = {};
	colorAttachment.format = swapchain.format;
	colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
	colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

	VkAttachmentReference colorAttachmentRef = {};
	colorAttachmentRef.attachment = 0;
	colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	VkSubpassDependency dependency = {};
	dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
	dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dependency.srcAccessMask = 0;
	dependency.dstSubpass = 0;
	dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

	VkSubpassDescription subpass = {};
	subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	subpass.colorAttachmentCount = 1;
	subpass.pColorAttachments = &colorAttachmentRef;

	VulkanDeleter<VkRenderPass> renderPass{ device, vk.vkDestroyRenderPass };

	VkRenderPassCreateInfo renderPassInfo = {};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	renderPassInfo.attachmentCount = 1;
	renderPassInfo.pAttachments = &colorAttachment;
	renderPassInfo.subpassCount = 1;
	renderPassInfo.pSubpasses = &subpass;
	renderPassInfo.dependencyCount = 1;
	renderPassInfo.pDependencies = &dependency;

	if (vk.vkCreateRenderPass(device, &renderPassInfo, nullptr, renderPass.replace()) != VK_SUCCESS) {
		throw std::runtime_error("failed to create render pass!");
	}

	plb.setLayout(pipelineLayout)
		.setTopology(VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST)
		.setRenderPass(renderPass, 0);
	rpass = renderPass;
	VULKAN_LOG.println("JESUS asd");
	this->pipeline = plb.build(this->main_device);

	swapchain.framebuffers.resize(swapchain.imageViews.size());
	for (size_t i = 0; i < swapchain.imageViews.size(); i++) {
		VkImageView attachments[] = {
			swapchain.imageViews[i]
		};

		VkFramebufferCreateInfo framebufferInfo = {};
		framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebufferInfo.renderPass = rpass;
		framebufferInfo.attachmentCount = 1;
		framebufferInfo.pAttachments = attachments;
		framebufferInfo.width = swapchain.extent.width;
		framebufferInfo.height = swapchain.extent.height;
		framebufferInfo.layers = 1;

		if (vk.vkCreateFramebuffer(device, &framebufferInfo, nullptr, &swapchain.framebuffers[i]) != VK_SUCCESS) {
			throw DevaException("failed to create framebuffer!");
		}
	}

	VkCommandPoolCreateInfo poolInfo = {};
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.queueFamilyIndex = 0;
	poolInfo.flags = 0; // Optional
	VulkanDeleter<VkCommandPool> commandPool{ device, vk.vkDestroyCommandPool };
	if (vk.vkCreateCommandPool(device, &poolInfo, nullptr, commandPool.replace()) != VK_SUCCESS) {
		throw std::runtime_error("failed to create command pool!");
	}

	commandBuffers.resize(swapchain.framebuffers.size());

	VkCommandBufferAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = commandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = (uint32_t)commandBuffers.size();

	if (vk.vkAllocateCommandBuffers(device, &allocInfo, commandBuffers.data()) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate command buffers!");
	}

	for (size_t i = 0; i < commandBuffers.size(); i++) {
		VkCommandBufferBeginInfo beginInfo = {};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
		beginInfo.pInheritanceInfo = nullptr; // Optional

		vk.vkBeginCommandBuffer(commandBuffers[i], &beginInfo);
		VkRenderPassBeginInfo renderPassInfo = {};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = rpass;
		renderPassInfo.framebuffer = swapchain.framebuffers[i];
		renderPassInfo.renderArea.offset = { 0, 0 };
		renderPassInfo.renderArea.extent = swapchain.extent;
		VkClearValue clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };
		renderPassInfo.clearValueCount = 1;
		renderPassInfo.pClearValues = &clearColor;
		vk.vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
		vk.vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);
		vk.vkCmdDraw(commandBuffers[i], 3, 1, 0, 0);
		vk.vkCmdEndRenderPass(commandBuffers[i]);
		if (vk.vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS) {
			throw DevaException("failed to record command buffer!");
		}
	}

	VkSemaphoreCreateInfo semaphoreInfo = {};
	semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

	if (vk.vkCreateSemaphore(device, &semaphoreInfo, nullptr, &imageAvailableSemaphore) != VK_SUCCESS ||
		vk.vkCreateSemaphore(device, &semaphoreInfo, nullptr, &renderFinishedSemaphore) != VK_SUCCESS) {

		throw std::runtime_error("failed to create semaphores!");
	}
}


#undef max
#include <limits>
void VulkanRenderer::drawFrame() 
{
	auto &vk = main_device.getFunctionSet();
	auto device = main_device.getHandle();
	uint32_t imageIndex;
	vk.vkAcquireNextImageKHR(device, swapchain.handle, std::numeric_limits<uint64_t>::max(), imageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);

	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

	VkSemaphore waitSemaphores[] = { imageAvailableSemaphore };
	VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = waitSemaphores;
	submitInfo.pWaitDstStageMask = waitStages;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffers[imageIndex];
	VkSemaphore signalSemaphores[] = { renderFinishedSemaphore };
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = signalSemaphores;
	main_pdev.queueFamilies[0].queueCount;
	VkQueue q;
	VkQueue pq;

	vk.vkGetDeviceQueue(device, renderQueue, 0, &q);
	vk.vkGetDeviceQueue(device, renderQueue, 1, &pq);
	if (vk.vkQueueSubmit(q, 1, &submitInfo, VK_NULL_HANDLE) != VK_SUCCESS) {
		throw std::runtime_error("failed to submit draw command buffer!");
	}

	VkPresentInfoKHR presentInfo = {};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = signalSemaphores;
	VkSwapchainKHR swapChains[] = { swapchain.handle };
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = swapChains;
	presentInfo.pImageIndices = &imageIndex;
	presentInfo.pResults = nullptr; // Optional

	vk.vkQueuePresentKHR(pq, &presentInfo);
}


void VulkanRenderer::renderExample()
{
	drawFrame();
}