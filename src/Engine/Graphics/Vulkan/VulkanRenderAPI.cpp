#define DEVA_DO_NOT_DEFINE_UUID_OPERATORS_IN_STD

#define NOMINMAX
#include "VulkanRenderAPI.hpp"
#include "../../Preferences.hpp"

#include "VulkanPipelineBuilder.hpp"
#include "VulkanBufferMemoryIndex.hpp"

#include <DevaFramework\Core\Uuid.hpp>

#include <DevaFramework\Graphics\Image.hpp>
#include <DevaFramework\Graphics\Model.hpp>
#include <DevaFramework\Graphics\Vulkan\Common.hpp>
#include <DevaFramework\Graphics\Vulkan\VulkanCommandPool.hpp>
#include <DevaFramework\Graphics\Vulkan\VulkanBuffer.hpp>
#include <DevaFramework\Graphics\Vulkan\VulkanMemory.hpp>

#include <DevaFramework\Util\Time.hpp>



#include <limits>
#include <unordered_set>


using namespace DevaFramework;
using namespace DevaEngine;

using DevaFramework::Vulkan::LOG_VULKAN;

namespace DevaEngine {



	VulkanDescriptorPool::VulkanDescriptorPool(
		const DevaFramework::VulkanDevice &dev,
		const std::vector<VulkanDescriptorSetLayout::LayoutModel> &layouts,
		uint32_t maxSets)
		: device(dev), supportedLayouts(layouts)
	{
		auto device = dev.handle;
		auto &vk = dev.vk;


		std::unordered_map<VkDescriptorType, uint32_t> poolSizes;
		for (auto i = 0;i < layouts.size();i++) {
			for (auto j : layouts[i].bindings) {
				auto &result = poolSizes.find(j.second.descriptorType);
				if (result == poolSizes.end()) poolSizes.insert({ j.second.descriptorType, j.second.descriptorCount });
				else if (result->second < j.second.descriptorCount) result->second = j.second.descriptorCount;
			}
		}

		std::vector<VkDescriptorPoolSize> sizes;
		for (auto i : poolSizes) {
			VkDescriptorPoolSize psize;
			psize.type = i.first;
			psize.descriptorCount = i.second;
			sizes.push_back(psize);
		}

		VkDescriptorPoolCreateInfo cinfo;
		cinfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		cinfo.pNext = nullptr;
		cinfo.flags = 0;
		cinfo.poolSizeCount = static_cast<uint32_t>(sizes.size());
		cinfo.pPoolSizes = sizes.data();
		cinfo.maxSets = maxSets;

		if (vk.vkCreateDescriptorPool(device, &cinfo, nullptr, &poolHandle) != VK_SUCCESS)
			throw DevaException("Could not create descriptor pool");
	}

	VkDescriptorPool VulkanDescriptorPool::getHandle() const {
		return poolHandle;
	}

	std::vector<VkDescriptorSet> VulkanDescriptorPool::allocateDescriptorSets(const std::vector<VkDescriptorSetLayout> &layouts, size_t count) {
		VkDescriptorSetAllocateInfo info;
		info.descriptorPool = poolHandle;
		info.descriptorSetCount = static_cast<uint32_t>(count);
		info.pNext = nullptr;
		info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		info.pSetLayouts = layouts.data();

		std::vector<VkDescriptorSet> sets(count);
		if (device.vk.vkAllocateDescriptorSets(device.handle, &info, sets.data()) != VK_SUCCESS)
			throw DevaException("Could not allocated descriptor sets");

		return sets;
	}

	void VulkanDescriptorPool::relinquishDescriptorSet(VkDescriptorSet dset)
	{
	}
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

	const VkInstanceCreateInfo INSTANCE_CREATE_INFO =
	{
		VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,                   //sType
		NULL,                                                     //pNext
		0,                                                        //flags - must be 0 as per current spec (2016/08/21)
		&APPLICATION_INFO,                                        //pApplicationInfo
		0,														  //enabledLayerCount
		nullptr,												  //ppEnabledLayerNames
		0,														  //enabledExtensionCount
		nullptr													  //ppEnabledExtensionNames
	};

	const char * DEVICE_EXTENSIONS[] =
	{
		VK_KHR_SWAPCHAIN_EXTENSION_NAME,
	};

	const VkPhysicalDeviceFeatures EMPTY_FEATURES;

	const bool VULKAN_LOADED = false;

	bool pickGPU(const VulkanInstance &instance, VkSurfaceKHR surface, VulkanPhysicalDevice * gpu, uint32_t * queueIndex)
	{
		auto vk = instance.vk;
		auto pdevs = instance.physicalDevices;
		for (auto &pdev : pdevs) {
			if (pdev.properties.deviceType != VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) continue;
			auto& supportedQueues = DevaFramework::Vulkan::deviceQueueFamiliesSupportSurface(instance, pdev.handle, surface);
			for (int i = 0;i < supportedQueues.size();i++)
			{
				auto& q = pdev.queueFamilyProperties[supportedQueues[i]];
				if ((q.queueFlags & VK_QUEUE_GRAPHICS_BIT) == 0) continue;

				VkBool32 supportsPresent = DevaFramework::Vulkan::doesDeviceQueueSupportSurface(instance, pdev, supportedQueues[i], surface);
				if (supportsPresent) {
					*queueIndex = supportedQueues[i];
					*gpu = pdev;
					return true;
				}
			}
		}
		return false;
	}

	VulkanDevice createLogicalDevice(const VulkanInstance& instance, const VulkanPhysicalDevice &pdev, uint32_t queueIndex)
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
			if (!DevaFramework::Vulkan::doesDeviceSupportExtension(pdev, ext))
				throw DevaException("Cannot create VulkanDevice: Unsupported extension " + std::string(ext));
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
		if (pdev.features.fillModeNonSolid) dev_cinfo.pEnabledFeatures = &features;

		return DevaFramework::Vulkan::createDevice(instance, pdev, dev_cinfo);
	}

	std::pair<VkDescriptorSetLayout, VulkanDescriptorSetLayout::LayoutModel> createLayout(
		const VulkanDevice &device,
		const std::vector<VkDescriptorSetLayoutBinding> &bindings,
		VkDescriptorSetLayoutCreateFlags flags = 0) {

		auto dev = device.handle;
		auto &vk = device.vk;

		VkDescriptorSetLayoutCreateInfo cinfo;
		cinfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		cinfo.pNext = nullptr;
		cinfo.flags = flags;
		cinfo.bindingCount = static_cast<uint32_t>(bindings.size());
		cinfo.pBindings = bindings.data();

		VkDescriptorSetLayout layout;

		if (vk.vkCreateDescriptorSetLayout(dev, &cinfo, nullptr, &layout) != VK_SUCCESS) {
			throw DevaException("Could not create descriptor set layout");
		}

		VulkanDescriptorSetLayout::LayoutModel layoutinfo;
		for (auto i : bindings) {
			VulkanDescriptorSetLayout::LayoutModel::Binding binfo;
			binfo.descriptorType = i.descriptorType;
			binfo.descriptorCount = i.descriptorCount;
			layoutinfo.bindings.insert({ i.binding, binfo });
		}

		return { layout, layoutinfo };
	}
}

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

void VulkanRenderAPI::onInit(const Preferences &prefs) {

	if (!VULKAN_LOADED) DevaFramework::Vulkan::LoadVulkan();

	auto layers = prefs.getPreference("vklayers");
	std::vector<const char*> layerPointers;
	std::vector<std::string> layerStrings;
	if (layers.has_value() && layers.type() == typeid(std::vector<std::string>)) {
		layerStrings = std::any_cast<std::vector<std::string>>(layers);
		for (auto i = 0;i < layerStrings.size();i++) {
			layerPointers.push_back(layerStrings[i].c_str());
		}
	}

	auto extensions = prefs.getPreference("vkextensions");
	std::vector<const char*> extensionPointers;
	std::vector<std::string> extensionStrings;
	if (extensions.has_value() && extensions.type() == typeid(std::vector<std::string>)) {
		extensionStrings = std::any_cast<std::vector<std::string>>(extensions);
		for (auto i = 0;i < extensionStrings.size();i++) {
			if (DevaFramework::Vulkan::instanceExtensionAvailable(extensionStrings[i])) {
				extensionPointers.push_back(extensionStrings[i].c_str());
			}
		}
	}

	VkInstanceCreateInfo instanceInfo(INSTANCE_CREATE_INFO);
	instanceInfo.enabledLayerCount = layerPointers.size();
	instanceInfo.ppEnabledLayerNames = layerPointers.data();
	instanceInfo.enabledExtensionCount = extensionPointers.size();
	instanceInfo.ppEnabledExtensionNames = extensionPointers.data();
	this->instance = DevaFramework::Vulkan::createInstance(instanceInfo);

	auto &vk = instance.vk;
	callback = DevaFramework::Vulkan::attachDebugCallback(instance, &debug, VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT);
	bufmemIndex = std::make_unique<VulkanBufferMemoryIndex>();
}

void VulkanRenderAPI::onSetupRenderTargetWindow(const Window &wnd) {
	surface = DevaFramework::Vulkan::createSurfaceForWindow(instance, wnd);

	VulkanPhysicalDevice gpu;
	uint32_t queueIndex = 0;
	if (!::pickGPU(instance, surface, &gpu, &queueIndex)) throw DevaException("Could not find suitable GPU and/or queue");
	this->main_device = ::createLogicalDevice(instance, gpu, queueIndex);
	ENGINE_LOG.v(strformat("Using GPU: {}", gpu.properties.deviceName));

	this->renderQueue = DevaFramework::Vulkan::getDeviceQueue(main_device, queueIndex, 0);
	this->queueBuffer = VulkanQueueSubmitBuffer(renderQueue);

	attachToWindow(wnd);
	createRenderPass();

	{
		fence = DevaFramework::Vulkan::createFence(main_device, VK_FENCE_CREATE_SIGNALED_BIT);
		imageAvailableSemaphore = DevaFramework::Vulkan::createSemaphore(main_device);
		renderFinishedSemaphore = DevaFramework::Vulkan::createSemaphore(main_device);
	}

	createPipeline();
}

void VulkanRenderAPI::onSetupRenderTargetImage(const Image &img) {
	throw DevaUnsupportedOperationException("Image rendering not supported yet");
}

void VulkanRenderAPI::attachToWindow(const Window &wnd)
{
	auto dev = instance.physicalDevices[0];
	auto vk = instance.vk;

	auto surfaceprops = DevaFramework::Vulkan::getSurfaceProperties(instance, dev, surface);

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
		renderQueue.familyIndex
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

	this->swapchain = DevaEngine::Vulkan::createSwapchain(this->main_device, swapchainCreateInfo);
}

void VulkanRenderAPI::createRenderPass() {
	VkAttachmentDescription colorAttachment = {};
	colorAttachment.format = swapchain.format;
	colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
	colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
	renderPass.attachments.push_back(colorAttachment);

	VkAttachmentReference colorAttachmentRef = { 0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL };
	colorAttachmentRef.attachment = 0;
	colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	VkSubpassDescription subpass = {};
	subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	subpass.colorAttachmentCount = 1;
	subpass.pColorAttachments = &colorAttachmentRef;
	renderPass.subpasses.push_back({ VK_PIPELINE_BIND_POINT_GRAPHICS,{ { 0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL } } });

	VkRenderPassCreateInfo renderPassInfo = {};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	renderPassInfo.attachmentCount = 1;
	renderPassInfo.pAttachments = &colorAttachment;
	renderPassInfo.subpassCount = 1;
	renderPassInfo.pSubpasses = &subpass;
	renderPassInfo.dependencyCount = 0;
	renderPassInfo.pDependencies = nullptr;

	if (main_device.vk.vkCreateRenderPass(main_device.handle, &renderPassInfo, nullptr, &renderPass.handle) != VK_SUCCESS) {
		throw std::runtime_error("failed to create render pass!");
	}
}

VulkanHandle<VkDescriptorPool> dpool;
#include <DevaFramework\Graphics\ImageReaders.hpp>
void VulkanRenderAPI::createPipeline()
{
	auto vert = DevaFramework::Vulkan::loadShaderFromFile(this->main_device, "../shaders/vshader.spv");
	auto frag = DevaFramework::Vulkan::loadShaderFromFile(this->main_device, "../shaders/fshader.spv");

	VulkanGraphicsPipelineBuilder plb;
	plb.attachShader(vert, VK_SHADER_STAGE_VERTEX_BIT, "main")
		.attachShader(frag, VK_SHADER_STAGE_FRAGMENT_BIT, "main")
		.outputExtent(swapchain.extent);

	auto &vk = main_device.vk;
	auto device = main_device.handle;

	for (size_t i = 0; i < swapchain.imageViews.size(); i++) {
		VkImageView attachments[] = {
			swapchain.imageViews[i]
		};

		VkFramebufferCreateInfo framebufferInfo = {};
		framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebufferInfo.renderPass = renderPass.handle;
		framebufferInfo.attachmentCount = 1;
		framebufferInfo.pAttachments = attachments;
		framebufferInfo.width = swapchain.extent.width;
		framebufferInfo.height = swapchain.extent.height;
		framebufferInfo.layers = 1;

		if (vk.vkCreateFramebuffer(device, &framebufferInfo, nullptr, &swapchain.framebuffers[i]) != VK_SUCCESS) {
			throw DevaException("failed to create framebuffer!");
		}
	}

	plb.setTopology(VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST)
		.setRenderPass(renderPass.handle, 0);

	DevaFramework::Vulkan::VertexInputBinding vib(0, VK_VERTEX_INPUT_RATE_VERTEX, 28);
	vib.addAttribute(DevaFramework::Vulkan::makeVAD(0, 0, VK_FORMAT_R32G32B32A32_SFLOAT, 0));
	vib.addAttribute(DevaFramework::Vulkan::makeVAD(1, 0, VK_FORMAT_R32G32B32_SFLOAT, 16));
	plb.addVertexInputBinding(vib);

	VkDescriptorSetLayoutBinding binding;
	binding.binding = 0;
	binding.descriptorCount = 1;
	binding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	binding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
	binding.pImmutableSamplers = nullptr;

	auto dslayout = createLayout(main_device, { binding });
	auto id = Uuid();
	dsLayouts.insert({ id, dslayout });
	uint32_t setn;
	plb.addDescriptorSetLayout(dslayout.first, &setn);
	dsLayoutPipelineMap.insert({ id, setn });

	dpoolManager = std::make_unique<VulkanDescriptorPool>(VulkanDescriptorPool(main_device, { dslayout.second }, { 2 }));

	this->pipeline = plb.build(this->main_device);

	renderPassRecord.pipeline = pipeline.getHandle();
	renderPassRecord.renderArea = swapchain.extent;
	renderPassRecord.clearVals = { { 0.0f, 0.0f, 0.0f, 0.0f } };
	renderPassRecord.renderPass = renderPass.handle;

	commandPool = DevaFramework::Vulkan::createCommandPool(main_device, renderQueue.familyIndex, VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);
	commandBuffers.push_back(DevaFramework::Vulkan::allocateCommandBuffer(main_device, commandPool, VK_COMMAND_BUFFER_LEVEL_PRIMARY));
}

std::tuple<VkImageMemoryBarrier, VkPipelineStageFlags, VkPipelineStageFlags> transitionImageLayout(VkImage image, VkImageLayout oldLayout, VkImageLayout newLayout) {
	VkImageMemoryBarrier barrier = {};
	barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
	barrier.oldLayout = oldLayout;
	barrier.newLayout = newLayout;

	barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	barrier.image = image;
	barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	barrier.subresourceRange.baseMipLevel = 0;
	barrier.subresourceRange.levelCount = 1;
	barrier.subresourceRange.baseArrayLayer = 0;
	barrier.subresourceRange.layerCount = 1;
	barrier.srcAccessMask = 0; // TODO
	barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT; // TODO

	VkPipelineStageFlags sourceStage;
	VkPipelineStageFlags destinationStage;

	if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) {
		barrier.srcAccessMask = 0;
		barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

		sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
		destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
	}
	else if (oldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
		barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
		barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

		sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
		destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
	}
	else {
		throw std::invalid_argument("unsupported layout transition!");
	}

	return { barrier, sourceStage, destinationStage };
}

Uuid VulkanRenderAPI::loadImage(const Image &img) {
	auto dev = this->main_device.handle;
	auto vk = this->main_device.vk;

	size_t imageSize = img.getData().size();
	Uuid bufid = bufmemIndex->addBuffer(DevaFramework::Vulkan::createBuffer(
		this->main_device,
		0,
		imageSize,
		VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
		VK_SHARING_MODE_EXCLUSIVE));
	Uuid memid = bufmemIndex->addMemory(DevaFramework::Vulkan::allocateMemoryForBuffer(
		this->main_device,
		bufmemIndex->getBuffer(bufid),
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT));
	bufmemIndex->bindBufferMemory(bufid, memid, main_device, 0);

	void* mem = nullptr;
	vk.vkMapMemory(dev, bufmemIndex->getMemory(memid).handle, 0, imageSize, 0, &mem);
	memcpy(mem, img.getData().data(), imageSize);
	vk.vkUnmapMemory(dev, bufmemIndex->getMemory(memid).handle);

	VulkanImage image;

	VkImageCreateInfo imageInfo = {};
	imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	imageInfo.imageType = VK_IMAGE_TYPE_2D;
	imageInfo.extent.width = static_cast<uint32_t>(img.width);
	imageInfo.extent.height = static_cast<uint32_t>(img.height);
	imageInfo.extent.depth = 1;
	imageInfo.mipLevels = 1;
	imageInfo.arrayLayers = 1;
	imageInfo.format = VK_FORMAT_R8G8B8A8_UNORM;
	imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
	imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	imageInfo.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
	imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
	imageInfo.flags = 0; // Optional

	VkResult res;
	res = vk.vkCreateImage(dev, &imageInfo, nullptr, &image.handle);
	if (res != VK_SUCCESS) {
		throw DevaException("Could not create image");
	}

	VulkanMemory imgmem = DevaFramework::Vulkan::allocateMemoryForImage(main_device, image, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
	image.sharingMode = imageInfo.sharingMode;
	image.size = imgmem.size;
	image.usage = imageInfo.usage;

	Uuid id = Uuid();
	mImages.insert({ id, image });

	vk.vkBindImageMemory(dev, image.handle, imgmem.handle, 0);

	VkSubmitInfo submitInfo = {};
	VulkanCommandBuffer buffer = DevaFramework::Vulkan::allocateCommandBuffer(main_device, commandPool, VK_COMMAND_BUFFER_LEVEL_PRIMARY);

	DevaFramework::Vulkan::beginCommandBuffer(main_device, buffer.handle, VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);
	auto barrier = transitionImageLayout(image.handle, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
	vk.vkCmdPipelineBarrier(buffer.handle, std::get<1>(barrier), std::get<2>(barrier), 0, 0, nullptr, 0, nullptr, 1, &std::get<0>(barrier));

	VkBufferImageCopy region = {};
	region.bufferOffset = 0;
	region.bufferRowLength = 0;
	region.bufferImageHeight = 0;

	region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	region.imageSubresource.mipLevel = 0;
	region.imageSubresource.baseArrayLayer = 0;
	region.imageSubresource.layerCount = 1;

	region.imageOffset = { 0, 0, 0 };
	region.imageExtent = {
		img.width,
		img.height,
		1
	};

	vk.vkCmdCopyBufferToImage(buffer.handle, bufmemIndex->getBuffer(bufid).handle, image.handle, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

	barrier = transitionImageLayout(image.handle, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

	vk.vkCmdPipelineBarrier(buffer.handle, std::get<1>(barrier), std::get<2>(barrier), 0, 0, nullptr, 0, nullptr, 1, &std::get<0>(barrier));

	vk.vkEndCommandBuffer(buffer.handle);

	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &buffer.handle;

	vk.vkResetFences(dev, 1, &fence);
	vk.vkQueueSubmit(renderQueue.handle, 1, &submitInfo, fence);
	vk.vkWaitForFences(dev, 1, &fence, VK_TRUE, 100000000);

	vk.vkFreeCommandBuffers(dev, this->commandPool.handle, 1, &buffer.handle);
	bufmemIndex->removeBuffer(bufid, true);

	return Uuid();
}

#include"VulkanPresenter.hpp"

void VulkanRenderAPI::drawScene() {
	auto &vk = main_device.vk;
	auto device = main_device.handle;

	VkResult res = vk.vkWaitForFences(device, 1, &fence, VK_TRUE, std::numeric_limits<uint32_t>::max());
	if (res != VK_SUCCESS) LOG.w("FENCE NOT COMPLETE " + strm(res));
	vk.vkResetFences(device, 1, &fence);

	vk.vkFreeCommandBuffers(device, commandPool.handle, 1, &commandBuffers[0].handle);
	commandBuffers[0] = DevaFramework::Vulkan::allocateCommandBuffer(main_device, commandPool, VK_COMMAND_BUFFER_LEVEL_PRIMARY);
	DevaFramework::Vulkan::beginCommandBuffer(main_device, commandBuffers[0].handle, VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT);

	for (auto& object : renderObjects) {
		/*auto &obj = object.second;
		VulkanBuffer& buf = bufmemIndex->getBuffer(obj.vertexBuffers);

		VulkanRenderObject vdi;
		vdi.vertexBuffers = { buf.handle };
		vdi.indexBuffer = buf.handle;
		vdi.indexOffset = obj.offsets().index;
		vdi.indexType = VK_INDEX_TYPE_UINT32;
		vdi.pipelineLayout = pipeline.getPipelineLayout();
		vdi.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		vdi.vertexOffsets = { obj.offsets().vertex };
		vdi.descriptorSets = { obj.getDescriptorSet() };
		vdi.indexCount = obj.indexCount();
		vdi.instanceCount = 1;
		vdi.firstIndex = 0;
		vdi.vertexOffset = 0;
		vdi.firstInstance = 0;*/
		renderPassRecord.objs.push_back(object.second.first);
	}

	uint32_t imageIndex;
	vk.vkAcquireNextImageKHR(device, swapchain.handle, std::numeric_limits<uint64_t>::max(), imageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);

	renderPassRecord.framebuffer = swapchain.framebuffers[imageIndex];

	Vulkan::recordRenderPass(main_device, commandBuffers[0].handle, renderPassRecord);

	if (vk.vkEndCommandBuffer(commandBuffers[0].handle) != VK_SUCCESS) {
		throw DevaException("failed to record command buffer!");
	}

	queueBuffer.enqueue(
		{ commandBuffers[0].handle },
		{ imageAvailableSemaphore },
		{ VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT },
		{ renderFinishedSemaphore });

	queueBuffer.flush(main_device, fence);

	DevaFramework::Vulkan::present(main_device, renderQueue.handle, { renderFinishedSemaphore }, { swapchain.handle }, { imageIndex });
}

void VulkanRenderAPI::onDestroy() {
	auto inst = this->instance.handle;
	auto &vki = this->instance.vk;

	auto dev = this->main_device.handle;
	auto &vkd = this->main_device.vk;

	if (inst != VK_NULL_HANDLE) {
		vkd.vkDeviceWaitIdle(dev);
		vkd.vkDestroyRenderPass(dev, renderPass.handle, nullptr);
		vkd.vkDestroySemaphore(dev, imageAvailableSemaphore, nullptr);
		vkd.vkDestroySemaphore(dev, renderFinishedSemaphore, nullptr);
		vkd.vkDestroyFence(dev, fence, nullptr);
		for (auto i : swapchain.imageViews) {
			vkd.vkDestroyImageView(dev, i, nullptr);
		}
		for (auto i : swapchain.framebuffers) {
			vkd.vkDestroyFramebuffer(dev, i, nullptr);
		}
		vkd.vkDestroySwapchainKHR(dev, this->swapchain.handle, nullptr);
		this->surface.replace();

		for (auto &i : dsLayouts) {
			vkd.vkDestroyDescriptorSetLayout(dev, i.second.first, nullptr);
		}

		vkd.vkDestroyDescriptorPool(dev, dpoolManager->getHandle(), nullptr);

		auto leftover = bufmemIndex->clear();
		for (auto &i : leftover.first) {
			//vkd.vkDestroyBuffer(dev, i.handle, nullptr);
			DevaFramework::Vulkan::destroyObject(main_device, i);
		}
		leftover.first.clear();
		for (auto &i : leftover.second) {
			//vkd.vkFreeMemory(dev, i.handle, nullptr);
			DevaFramework::Vulkan::destroyObject(main_device, i);
		}
		leftover.second.clear();
		DevaFramework::Vulkan::destroyObject(main_device, commandPool);
		//this->dpoolManager->clear();
		vkd.vkDestroyPipelineLayout(dev, pipeline.getPipelineLayout(), nullptr);
		vkd.vkDestroyPipeline(dev, pipeline.getHandle(), nullptr);


		vki.vkDestroyDebugReportCallbackEXT(inst, callback, nullptr);

		DevaFramework::Vulkan::destroyObject(main_device);
		DevaFramework::Vulkan::destroyObject(instance);
	}
}

void VulkanRenderAPI::loadObject(const RenderObjectID &id, const RenderObject &object) {

	auto dev = main_device.handle;
	auto &vk = main_device.vk;

	auto &m = *object.model;

	size_t mvpsize = 16 * sizeof(float);
	size_t vsize = m.vertexCount() * m.vertexSize();
	size_t isize = m.faceIndices().size() * sizeof(uint32_t);
	size_t datasize = vsize + isize + mvpsize;

	VulkanBufferMemoryIndex::BufID bufid(VulkanBufferMemoryIndex::BufID::NULL_ID);
	for (auto id : bufmemIndex->getUnmappedBuffers()) {
		auto &buf = bufmemIndex->getBuffer(id);
		if (buf.size >= datasize) {
			bufid = id;
			break;
		}
	}

	if (bufid == Uuid::NULL_ID) {
		bufid = bufmemIndex->addBuffer(DevaFramework::Vulkan::createBuffer(main_device, 0, datasize, VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_SHARING_MODE_EXCLUSIVE));
	}

	auto &buf = bufmemIndex->getBuffer(bufid);

	VulkanBufferMemoryIndex::MemID memid = Uuid::NULL_ID;

	auto memories = bufmemIndex->getUnmappedMemoryBlocks();
	for (auto id : memories) {
		auto &mem = bufmemIndex->getMemory(id);
		if (DevaFramework::Vulkan::isBufferCompatibleWithMemory(buf, mem)) {
			memid = id;
			break;
		}
	}
	if (memid == Uuid::NULL_ID) {
		memid = bufmemIndex->addMemory(DevaFramework::Vulkan::allocateMemoryForBuffer(main_device, buf, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT));
	}

	auto &mem = bufmemIndex->getMemory(memid);
	bufmemIndex->bindBufferMemory(bufid, memid, main_device, 0);

	void* memory = nullptr;
	VkDeviceSize offset = mvpsize;
	vk.vkMapMemory(dev, mem.handle, offset, vsize, 0, &memory);
	memcpy(memory, m.vertexData().data(), vsize);
	vk.vkUnmapMemory(dev, mem.handle);

	offset = offset + vsize;
	vk.vkMapMemory(dev, mem.handle, offset, isize, 0, &memory);
	memcpy(memory, m.faceIndices().data(), isize);
	vk.vkUnmapMemory(dev, mem.handle);

	VkDescriptorSet dset = dpoolManager->allocateDescriptorSets({ dsLayouts.begin()->second.first }, 1)[0];
	VkDescriptorBufferInfo dbufinfo;
	dbufinfo.buffer = buf.handle;
	dbufinfo.offset = 0;
	dbufinfo.range = mvpsize;
	VkWriteDescriptorSet descriptorWrite = {};
	descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	descriptorWrite.dstSet = dset;
	descriptorWrite.dstBinding = 0;
	descriptorWrite.dstArrayElement = 0;
	descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	descriptorWrite.descriptorCount = 1;
	descriptorWrite.pBufferInfo = &dbufinfo;
	descriptorWrite.pImageInfo = nullptr; // Optional
	descriptorWrite.pTexelBufferView = nullptr; // Optional
	vk.vkUpdateDescriptorSets(dev, 1, &descriptorWrite, 0, nullptr);

	VulkanRenderObject drawobj;

	drawobj.vertexBuffers = { buf.handle };
	drawobj.vertexOffsets = { mvpsize };

	drawobj.indexBuffer = buf.handle;
	drawobj.indexOffset = vsize + mvpsize;
	drawobj.indexCount = m.faceIndices().size();
	drawobj.indexType = VK_INDEX_TYPE_UINT32;
	drawobj.firstIndex = 0;

	drawobj.pipelineLayout = pipeline.getPipelineLayout();
	drawobj.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;

	drawobj.mvpBuffer = buf.handle;
	drawobj.mvpOffset = 0;
	drawobj.descriptorSets = { dset };

	drawobj.firstInstance = 0;
	drawobj.instanceCount = 1;
	drawobj.vertexOffset = 0;

	VulkanRenderObjectResources vroi;
	vroi.indexBuffer = bufid;
	vroi.mvpBuffer = bufid;
	vroi.vertexBuffers = { bufid };

	renderObjects.insert({ id, {drawobj, vroi} });
}

void VulkanRenderAPI::unloadObject(const RenderObjectID &id) {

	auto dev = main_device.handle;
	auto &vk = main_device.vk;

	auto obj = renderObjects.find(id);
	if (obj == renderObjects.end()) {
		throw DevaInvalidArgumentException(strformat("Object ID {} does not exist in renderer", (std::string)id));
	}

	auto &vro = obj->second.first;
	auto &vroi = obj->second.second;

	std::unordered_set<DevaFramework::Vulkan::VulkanBufferID> bufids;
	bufids.insert(vroi.indexBuffer);
	bufids.insert(vroi.mvpBuffer);
	bufids.insert(vroi.vertexBuffers.begin(), vroi.vertexBuffers.end());
	for (auto &i : bufids) {
		bufmemIndex->removeBuffer(i, false);
	}

	renderObjects.erase(obj);
}

void VulkanRenderAPI::updateObjectMVP(const RenderObjectID &id, const mat4 &mvp) {
	auto dev = main_device.handle;
	auto &vk = main_device.vk;

	auto obji = renderObjects.find(id);
	if (obji == renderObjects.end()) {
		throw DevaInvalidArgumentException(strformat("Object ID {} does not exist in renderer", (std::string)id));
	}
	auto &obj = obji->second;

	auto &mem = bufmemIndex->getMemory(bufmemIndex->getBufferMemory(obj.second.mvpBuffer));

	void* memory = nullptr;

	vk.vkWaitForFences(dev, 1, &fence, VK_TRUE, 100);
	vk.vkMapMemory(dev, mem.handle, obj.first.mvpOffset, sizeof(float) * 16, 0, &memory);
	auto rawmvp = mvp.rawData();
	memcpy(memory, (const unsigned char*)rawmvp.first, rawmvp.second * sizeof(float));
	vk.vkUnmapMemory(dev, mem.handle);
}