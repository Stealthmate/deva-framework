#define NOMINMAX
#include "VulkanRenderer.hpp"

#include "VulkanPipelineBuilder.hpp"

#include <DevaFramework\Graphics\Vulkan\Common.hpp>
#include <DevaFramework\Graphics\Vulkan\VulkanCommandPool.hpp>
#include <DevaFramework\Graphics\Vulkan\VulkanBuffer.hpp>
#include <DevaFramework\Graphics\Vulkan\VulkanMemory.hpp>
#include <limits>
#include <thread>

using namespace DevaFramework;
using namespace DevaEngine;

VertexBuffer createVertexBuffer(float f = 0.0f) {
	//LOG.i(strm(f));
	ByteBuffer buf(72);
	buf << +0.0f + f << -0.5f << +0.0f << +1.0f << +0.0f + f << +1.0f;
	buf << +0.5f << +0.5f << +0.0f << +0.0f << +1.0f << +1.0f;
	buf << -0.5f << +0.5f << +0.0f << +0.0f << +0.0f + f << +1.0f;


	std::vector<VertexDataElementDescription> elements;
	VertexDataElementDescription desc;
	desc.componentBitsizes = { 32, 32, 32 };
	desc.size = 12;
	desc.type = VertexComponentType::FLOAT;
	elements.push_back(desc);
	elements.push_back(desc);

	return VertexBuffer(buf.buf(), 3, elements, INTERLEAVED);
}


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
		VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,                   //sType
		NULL,                                                     //pNext
		0,                                                        //flags - must be 0 as per current spec (2016/08/21)
		&APPLICATION_INFO,                                        //pApplicationInfo
		(uint32_t) sizeof INSTANCE_LAYERS / sizeof(const char*),  //enabledLayerCount
		INSTANCE_LAYERS,                                          //ppEnabledLayerNames
		(uint32_t)N_EXTENSIONS,                                  //enabledExtensionCount
		EXTENSIONS                                                //ppEnabledExtensionNames
	};

	const char * DEVICE_EXTENSIONS[] =
	{
		VK_KHR_SWAPCHAIN_EXTENSION_NAME,
	};

	const char * DEVICE_FEATURES[] =
	{
		"ASD"
	};

	const VkPhysicalDeviceFeatures EMPTY_FEATURES;

	const bool VULKAN_LOADED = false;

	bool pickGPU(const VulkanInstance &instance, VkSurfaceKHR surface, VulkanPhysicalDeviceTraits * gpu, uint32_t * queueIndex)
	{
		auto vk = instance.vk();
		auto pdevs = instance.getPhysicalDevices();
		for (auto &pdev : pdevs) {
			if (pdev.properties().deviceType != VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) continue;
			auto& supportedQueues = Vulkan::deviceQueueFamiliesSupportSurface(instance, pdev.handle(), surface);
			for (int i = 0;i < supportedQueues.size();i++)
			{
				auto& q = pdev.queueFamilyProperties()[supportedQueues[i]];
				if ((q.queueFlags & VK_QUEUE_GRAPHICS_BIT) == 0) continue;

				VkBool32 supportsPresent;
				vk.vkGetPhysicalDeviceSurfaceSupportKHR(pdev.handle(),
					supportedQueues[i],
					surface,
					&supportsPresent);
				if (supportsPresent == VK_TRUE) {
					*queueIndex = supportedQueues[i];
					*gpu = pdev;
					return true;
				}
			}
		}
		return false;
	}

	VulkanDevice createLogicalDevice(const VulkanInstance& instance, const VulkanPhysicalDeviceTraits &pdev, uint32_t queueIndex)
	{
		std::vector<float> priorities = { 1.0f };
		VkDeviceQueueCreateInfo q_cinfo;
		q_cinfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		q_cinfo.pNext = nullptr;
		q_cinfo.queueCount = 1;
		q_cinfo.queueFamilyIndex = queueIndex;
		q_cinfo.pQueuePriorities = priorities.data();
		q_cinfo.flags = 0;
		for (auto ext : DEVICE_EXTENSIONS)
		{
			bool supported = false;
			for (auto &devext : pdev.extensionProperties())
			{
				supported = std::string(devext.extensionName).compare(ext) == 0;
				if (supported) break;
			}
			if (!supported) throw DevaException("Cannot create VulkanDevice: Unsupported extension " + std::string(ext));
		}

		VkDeviceCreateInfo dev_cinfo;
		dev_cinfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		dev_cinfo.pNext = nullptr;
		dev_cinfo.flags = 0;
		dev_cinfo.queueCreateInfoCount = 1;
		dev_cinfo.pQueueCreateInfos = &q_cinfo;
		dev_cinfo.enabledLayerCount = 0;
		dev_cinfo.ppEnabledLayerNames = nullptr;
		dev_cinfo.enabledExtensionCount = sizeof DEVICE_EXTENSIONS / sizeof(const char*);
		dev_cinfo.ppEnabledExtensionNames = DEVICE_EXTENSIONS;
		VkPhysicalDeviceFeatures features = EMPTY_FEATURES;
		features.fillModeNonSolid = VK_TRUE;
		if (pdev.features().fillModeNonSolid) dev_cinfo.pEnabledFeatures = &features;

		return VulkanDevice(instance, pdev, dev_cinfo);
	}
}


VulkanRenderer::VulkanRenderer() : instance(VulkanInstance()) {}

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
	switch (flags) {
	case VK_DEBUG_REPORT_ERROR_BIT_EXT: {
		LOG_VULKAN.e("Error from: " + strm(pLayerPrefix));
		LOG_VULKAN.e(pMessage);
	} break;
	case VK_DEBUG_REPORT_DEBUG_BIT_EXT: {
		LOG_VULKAN.d(pLayerPrefix);
		LOG_VULKAN.d(pMessage);
	} break;
	case VK_DEBUG_REPORT_WARNING_BIT_EXT:
	{
		LOG_VULKAN.w(pLayerPrefix);
		LOG_VULKAN.w(pMessage);

	}break;
	}
	return VK_FALSE;
}

VkDebugReportCallbackEXT callback;
VulkanRenderer::VulkanRenderer(const Window &wnd)
	:instance(VulkanInstance())
{
	if (!VULKAN_LOADED) LoadVulkan();

	this->instance = VulkanInstance::create(INSTANCE_CREATE_INFO);

	auto &vk = instance.vk();

	/* Setup callback creation information */
	VkDebugReportCallbackCreateInfoEXT callbackCreateInfo;
	callbackCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CREATE_INFO_EXT;
	callbackCreateInfo.pNext = nullptr;
	callbackCreateInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
	callbackCreateInfo.pfnCallback = &debug;
	callbackCreateInfo.pUserData = nullptr;

	/* Register the callback */
	VkResult result = vk.vkCreateDebugReportCallbackEXT(instance.handle(), &callbackCreateInfo, nullptr, &callback);

	this->surface = Vulkan::createSurfaceFromWindow(instance, wnd);
	VulkanPhysicalDeviceTraits gpu;
	uint32_t queueIndex = 0;
	if (!::pickGPU(instance, surface, &gpu, &queueIndex)) throw DevaException("Could not find suitable GPU and/or queue");
	this->main_device = ::createLogicalDevice(instance, gpu, queueIndex);
	ENGINE_LOG.i(main_device.physicalDeviceTraits().to_string());
	ENGINE_LOG.v(strformat("Using GPU: {}", gpu.properties().deviceName));

	this->renderQueue = queueIndex;

	attachToWindow(wnd);
	createPipeline();
}

void VulkanRenderer::attachToWindow(const Window &wnd)
{
	auto dev = instance.getPhysicalDevices()[0];
	auto vk = instance.vk();

	unsigned int queue = UINT_MAX;
	auto & queues = Vulkan::deviceQueueFamiliesSupportSurface(instance, dev.handle(), surface);

	this->renderQueue = 0;

	auto surfaceprops = dev.getSurfaceProperties(instance, this->surface);

	uint32_t formatCount = static_cast<uint32_t>(surfaceprops.formats.size());
	if (formatCount == 1 && surfaceprops.formats[0].format == VK_FORMAT_UNDEFINED)
		this->colorFormat = VK_FORMAT_B8G8R8A8_UNORM;
	else {
		if (formatCount == 0)
			throw DevaExternalFailureException("Vulkan", "Device has no surface formats!");
		this->colorFormat = surfaceprops.formats[0].format;
	}
	this->colorSpace = surfaceprops.formats[0].colorSpace;

	DevaExternalFailureException e = DevaExternalFailureException("Vulkan", "Vulkan error");

	VkExtent2D swapchainExtent = {};

	if (surfaceprops.capabilities.currentExtent.width == -1 || surfaceprops.capabilities.currentExtent.height == -1) {
		swapchainExtent.width = wnd.getWidth() / 2;
		swapchainExtent.height = wnd.getHeight() / 2;
	}
	else {
		swapchainExtent = surfaceprops.capabilities.currentExtent;
	}

	VkPresentModeKHR presentMode = VK_PRESENT_MODE_FIFO_KHR;

	for (uint32_t i = 0; i < surfaceprops.presentModes.size(); i++) {
		if (surfaceprops.presentModes[i] == VK_PRESENT_MODE_MAILBOX_KHR) {
			presentMode = VK_PRESENT_MODE_MAILBOX_KHR;
			break;
		}

		if (surfaceprops.presentModes[i] == VK_PRESENT_MODE_IMMEDIATE_KHR)
			presentMode = VK_PRESENT_MODE_IMMEDIATE_KHR;
	}

	if (surfaceprops.capabilities.maxImageCount < 1) throw e;

	uint32_t imageCount = surfaceprops.capabilities.minImageCount + 1;
	if (imageCount > surfaceprops.capabilities.maxImageCount) imageCount = surfaceprops.capabilities.maxImageCount;

	uint32_t indices = {
		renderQueue
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
}
VulkanHandle<VkSemaphore> imageAvailableSemaphore;
VulkanHandle<VkSemaphore> renderFinishedSemaphore;
std::vector<VkCommandBuffer> commandBuffers;
VulkanMemory memory;
VkRenderPass renderPass;
void *devmem;
void VulkanRenderer::createPipeline()
{
	auto vert = Vulkan::loadShaderFromFile(this->main_device, "shaders/vert.spv");
	auto frag = Vulkan::loadShaderFromFile(this->main_device, "shaders/frag.spv");
	
	VulkanGraphicsPipelineBuilder plb;
	plb.attachShader(vert, VK_SHADER_STAGE_VERTEX_BIT, "main")
		.attachShader(frag, VK_SHADER_STAGE_FRAGMENT_BIT, "main")
		.outputExtent(swapchain.extent);

	auto &vk = main_device.vk();
	auto device = main_device.handle();


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

	VkSubpassDescription subpass = {};
	subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	subpass.colorAttachmentCount = 1;
	subpass.pColorAttachments = &colorAttachmentRef;

	VkRenderPassCreateInfo renderPassInfo = {};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	renderPassInfo.attachmentCount = 1;
	renderPassInfo.pAttachments = &colorAttachment;
	renderPassInfo.subpassCount = 1;
	renderPassInfo.pSubpasses = &subpass;
	renderPassInfo.dependencyCount = 0;
	renderPassInfo.pDependencies = nullptr;

	if (vk.vkCreateRenderPass(device, &renderPassInfo, nullptr, &renderPass) != VK_SUCCESS) {
		throw std::runtime_error("failed to create render pass!");
	}

	plb.setTopology(VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST)
		.setRenderPass(renderPass, 0);

	Vulkan::VertexInputBinding vib(0, VK_VERTEX_INPUT_RATE_VERTEX, 24);
	VkVertexInputAttributeDescription vad;
	vad.binding = 0;
	vad.format = VK_FORMAT_R32G32B32A32_SFLOAT;
	vad.location = 0;
	vad.offset = 0;
	vib.addAttribute(vad);
	vad.offset = 12;
	vad.location = 1;
	vib.addAttribute(vad);

	plb.addVertexInputBinding(vib);

	this->pipeline = plb.build(this->main_device);

	for (size_t i = 0; i < swapchain.imageViews.size(); i++) {
		VkImageView attachments[] = {
			swapchain.imageViews[i]
		};

		VkFramebufferCreateInfo framebufferInfo = {};
		framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebufferInfo.renderPass = renderPass;
		framebufferInfo.attachmentCount = 1;
		framebufferInfo.pAttachments = attachments;
		framebufferInfo.width = swapchain.extent.width;
		framebufferInfo.height = swapchain.extent.height;
		framebufferInfo.layers = 1;

		if (vk.vkCreateFramebuffer(device, &framebufferInfo, nullptr, &swapchain.framebuffers[i]) != VK_SUCCESS) {
			throw DevaException("failed to create framebuffer!");
		}
	}

	buffers.push_back(VulkanBuffer::create(main_device, 0, 72, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_SHARING_MODE_EXCLUSIVE));
	VulkanBuffer &buffer = buffers[0];

	memory = VulkanMemory::forBuffer(buffer, main_device, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	auto VERTEXBUFFER = createVertexBuffer();
	vk.vkMapMemory(device, memory.handle(), 0, buffer.size(), 0, &devmem);
	memcpy(devmem, VERTEXBUFFER.buffer().data(), VERTEXBUFFER.buffer().size());

	vk.vkBindBufferMemory(device, buffer.handle(), memory.handle(), 0);
	commandPool = VulkanCommandPool(main_device, renderQueue);
	commandBuffers.resize(swapchain.framebuffers.size());

	imageAvailableSemaphore = Vulkan::createSemaphore(main_device);
	renderFinishedSemaphore = Vulkan::createSemaphore(main_device);
}

float f = 0.0f;
float df = 0.01f;
bool drawn = false;

void VulkanRenderer::drawFrame()
{
	//if (drawn) return;
	auto &vk = main_device.vk();
	auto device = main_device.handle();

	if (f > 0.5f || f < -0.5f) df = -df;
	f += df;
	auto VERTEXBUFFER = createVertexBuffer(f);
	memcpy(devmem, VERTEXBUFFER.buffer().data(), VERTEXBUFFER.buffer().size());

	VkCommandBufferAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = commandPool.handle();
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
		renderPassInfo.renderPass = renderPass;
		renderPassInfo.framebuffer = swapchain.framebuffers[i];
		renderPassInfo.renderArea.offset = { 0, 0 };
		renderPassInfo.renderArea.extent = swapchain.extent;
		VkClearValue clearColor = { 1.0f, 1.0f, 1.0f, 1.0f };
		renderPassInfo.clearValueCount = 1;
		renderPassInfo.pClearValues = &clearColor;
		vk.vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
		vk.vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);
		VkDeviceSize offsets[] = { 0 };
		VkBuffer bufs[] = { buffers[0].handle() };
		vk.vkCmdBindVertexBuffers(commandBuffers[i], 0, 1, bufs, offsets);
		vk.vkCmdDraw(commandBuffers[i], static_cast<uint32_t>(VERTEXBUFFER.vertexCount()), 1, 0, 0);
		vk.vkCmdEndRenderPass(commandBuffers[i]);
		if (vk.vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS) {
			throw DevaException("failed to record command buffer!");
		}
	}


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
	auto & queues = main_device.getQueuesOfFamily(VK_QUEUE_GRAPHICS_BIT);
	if (queues.size() == 0)
		throw DevaException("0 queues");

	VkQueue q = queues[0].handle();
	if (vk.vkQueueSubmit(q, 1, &submitInfo, VK_NULL_HANDLE) != VK_SUCCESS) {
		throw std::runtime_error("failed to submit draw command buffer!");
	}

	VkPresentInfoKHR presentInfo = {};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = signalSemaphores;
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = &swapchain.handle;
	presentInfo.pImageIndices = &imageIndex;
	presentInfo.pResults = nullptr; // Optional

	vk.vkQueuePresentKHR(q, &presentInfo);
	drawn = true;
}


void VulkanRenderer::renderExample()
{
	drawFrame();
}

VulkanRenderer::VulkanRenderer(VulkanRenderer &&renderer) :
	instance(std::move(renderer.instance)),
	main_device(std::move(renderer.main_device)),
	swapchain(std::move(renderer.swapchain)),
	surface(std::move(renderer.surface)),
	colorFormat(renderer.colorFormat),
	colorSpace(renderer.colorSpace),
	commandPool(std::move(renderer.commandPool)),
	pipeline(std::move(renderer.pipeline)) {}

VulkanRenderer::~VulkanRenderer() {
	destroy();
}

void VulkanRenderer::destroy() {
	auto inst = this->instance.handle();
	auto &vki = this->instance.vk();

	auto dev = this->main_device.handle();
	auto &vkd = this->main_device.vk();

	if (inst != VK_NULL_HANDLE) {
		vkd.vkDeviceWaitIdle(dev);
		for (auto & b : buffers) {
			b.destroy();
		}
		memory.free();
		vkd.vkDestroyRenderPass(dev, renderPass, nullptr);
		imageAvailableSemaphore.replace();
		renderFinishedSemaphore.replace();
		vkd.vkDestroySwapchainKHR(dev, this->swapchain.handle, nullptr);
		this->surface.replace();
		vki.vkDestroyDebugReportCallbackEXT(inst, callback, nullptr);
		for (auto i : swapchain.framebuffers) {
			vkd.vkDestroyFramebuffer(dev, i, nullptr);
		}
		/*for (auto i : swapchain.images) {
			vkd.vkDestroyImage(dev, i, nullptr);
		}*/
		for (auto i : swapchain.imageViews) {
			vkd.vkDestroyImageView(dev, i, nullptr);
		}
		this->pipeline.replace();
		this->commandPool.replace();

	}
}

void VulkanRenderer::render(const Scene& scene) 
{
	auto &objs = scene.getAllObjects();
	for (auto &object : objs) {
		
	}
}