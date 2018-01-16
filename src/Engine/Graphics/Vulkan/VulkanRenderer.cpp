#define DEVA_DO_NOT_DEFINE_UUID_OPERATORS_IN_STD

#define NOMINMAX
#include "VulkanRenderer.hpp"

#include "VulkanPipelineBuilder.hpp"
#include "VulkanBufferMemoryIndex.hpp"

#include <DevaFramework\Graphics\Vulkan\Common.hpp>
#include <DevaFramework\Graphics\Vulkan\VulkanCommandPool.hpp>
#include <DevaFramework\Graphics\Vulkan\VulkanBuffer.hpp>
#include <DevaFramework\Graphics\Vulkan\VulkanMemory.hpp>
#include <DevaFramework\Util\Time.hpp>
#include <limits>
#include <unordered_set>
//#include <memory>


using namespace DevaFramework;
using namespace DevaEngine;

namespace DevaEngine {

	class VulkanRenderer::ImplSceneUpdateListener : public Scene::SceneUpdateObserver {
	public:

		VulkanRenderer& renderer;

		ImplSceneUpdateListener(VulkanRenderer& renderer) : renderer(renderer) {}

		virtual void onNewObject(const Scene &scene, const SceneObjectID &id, const DrawableObject &object);
		virtual void onObjectUpdated(const Scene &scene, const SceneObjectID &id, const DrawableObject &object);
		virtual void onObjectRemoved(const Scene &scene, const SceneObjectID &id, const DrawableObject &object);
	};

	VulkanDescriptorPool::VulkanDescriptorPool(
		const DevaFramework::VulkanDevice &dev,
		const std::vector<VulkanDescriptorSetLayout::LayoutModel> &layouts,
		uint32_t maxSets)
		: device(dev), supportedLayouts(layouts)
	{
		auto device = dev.handle();
		auto &vk = dev.vk();


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
		if (device.vk().vkAllocateDescriptorSets(device.handle(), &info, sets.data()) != VK_SUCCESS)
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

	std::pair<VkDescriptorSetLayout, VulkanDescriptorSetLayout::LayoutModel> createLayout(
		const VulkanDevice &device,
		const std::vector<VkDescriptorSetLayoutBinding> &bindings,
		VkDescriptorSetLayoutCreateFlags flags = 0) {

		auto dev = device.handle();
		auto &vk = device.vk();

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

VulkanRenderer::VulkanRenderer() :
	instance(VulkanInstance()),
	bufmemIndex(new VulkanBufferMemoryIndex()),
	sceneListener(new VulkanRenderer::ImplSceneUpdateListener(*this)) {}

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

VulkanRenderer::VulkanRenderer(const DevaFramework::Window &wnd) : VulkanRenderer()
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
VkRenderPass renderPass;
void *devmem;
VulkanHandle<VkDescriptorPool> dpool;
VulkanHandle<VkDescriptorSetLayout> descsetlayout;
VkDescriptorSet descSet;

void VulkanRenderer::createPipeline()
{
	auto vert = Vulkan::loadShaderFromFile(this->main_device, "../shaders/vshader.spv");
	auto frag = Vulkan::loadShaderFromFile(this->main_device, "../shaders/fshader.spv");

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
	//asd
	plb.setTopology(VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST)
		.setRenderPass(renderPass, 0);

	Vulkan::VertexInputBinding vib(0, VK_VERTEX_INPUT_RATE_VERTEX, 28);
	VkVertexInputAttributeDescription vad;
	vad.binding = 0;
	vad.format = VK_FORMAT_R32G32B32A32_SFLOAT;
	vad.location = 0;
	vad.offset = 0;
	vib.addAttribute(vad);
	vad.offset = 16;
	vad.location = 1;
	vad.format = VK_FORMAT_R32G32B32_SFLOAT;
	vib.addAttribute(vad);

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

	commandPool = VulkanCommandPool(main_device, renderQueue, VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);
	commandBuffers.resize(1);
	for (auto &cb : commandBuffers) cb = VK_NULL_HANDLE;

	VkCommandBufferAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = commandPool.handle();
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = (uint32_t)commandBuffers.size();

	if (vk.vkAllocateCommandBuffers(device, &allocInfo, commandBuffers.data()) != VK_SUCCESS) {
		throw DevaExternalFailureException("Vulkan", "Failed to allocate command buffers!");
	}

	VkFenceCreateInfo fence_cinfo;
	fence_cinfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fence_cinfo.flags = 0;
	fence_cinfo.pNext = nullptr;
	vk.vkCreateFence(device, &fence_cinfo, nullptr, &fence);

	imageAvailableSemaphore = Vulkan::createSemaphore(main_device);
	renderFinishedSemaphore = Vulkan::createSemaphore(main_device);

	VkDescriptorPoolSize dpoolsize;
	dpoolsize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	dpoolsize.descriptorCount = 1;
	VkDescriptorPoolCreateInfo dpoolcinfo;
	dpoolcinfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	dpoolcinfo.pNext = nullptr;
	dpoolcinfo.flags = 0;
	dpoolcinfo.poolSizeCount = 1;
	dpoolcinfo.pPoolSizes = &dpoolsize;
	dpoolcinfo.maxSets = 1;
}

float f = 0.0f;
float df = 0.01f;
bool drawn = false;
int i = 0;

template<class T>
struct HashHandle {
	size_t operator()(const T &obj) const {
		return (uintptr_t)obj.handle();
	}
};



void VulkanRenderer::drawFrame()
{
	//if (drawn) return;
	auto &vk = main_device.vk();
	auto device = main_device.handle();
	
	/*for (auto &i : renderObjects) {
		auto &mvp = currentScene->getObjectTransform(i.first);
		void *memory = nullptr;
		auto &mem = bufmemIndex->getMemory(bufmemIndex->getBufferMemory(i.second.buffer()));

		vk.vkMapMemory(device, mem.handle(), 0, 64, 0, &memory);
		memcpy(memory, mvp.asBytes().data(), 64);
		vk.vkUnmapMemory(device, mem.handle());
	}*/
	

	VkResult res = vk.vkWaitForFences(device, 1, &fence, VK_TRUE, 100);

	if (drawn) while (res == VK_TIMEOUT) res = vk.vkWaitForFences(device, 1, &fence, VK_TRUE, 100);
	if (res != VK_SUCCESS) LOG.w("FENCE NOT COMPLETE " + strm(res));

	if (i == swapchain.framebuffers.size()) i = 0;

	VkCommandBufferBeginInfo beginInfo = {};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
	beginInfo.pInheritanceInfo = nullptr; // Optional

	vk.vkBeginCommandBuffer(commandBuffers[0], &beginInfo);
	VkRenderPassBeginInfo renderPassInfo = {};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	renderPassInfo.renderPass = renderPass;
	renderPassInfo.framebuffer = swapchain.framebuffers[i];
	renderPassInfo.renderArea.offset = { 0, 0 };
	renderPassInfo.renderArea.extent = swapchain.extent;
	VkClearValue clearColor = { 0.0f, 0.0f, 0.0f, 0.0f };
	renderPassInfo.clearValueCount = 1;
	renderPassInfo.pClearValues = &clearColor;
	vk.vkCmdBeginRenderPass(commandBuffers[0], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
	vk.vkCmdBindPipeline(commandBuffers[0], VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.getHandle());

	bufmemIndex->purge();

	for (auto& object : renderObjects) {
		auto &obj = object.second;
		VulkanBuffer& buf = bufmemIndex->getBuffer(object.second.buffer());
		VkDeviceSize offsets[] = { obj.offsets().vertex };
		VkBuffer handle = buf.handle();
		VkDeviceSize offsetIndex = obj.offsets().index;
		VkDescriptorSet dset = obj.getDescriptorSet();
		
		vk.vkCmdBindVertexBuffers(commandBuffers[0], 0, 1, &handle, offsets);
		vk.vkCmdBindIndexBuffer(commandBuffers[0], handle, obj.offsets().index, VK_INDEX_TYPE_UINT32);
		vk.vkCmdBindDescriptorSets(commandBuffers[0], VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.getPipelineLayout(), 0, 1, &dset, 0, nullptr);
		vk.vkCmdDrawIndexed(commandBuffers[0], obj.indexCount(), 1, 0, 0, 0);
	}

	vk.vkCmdEndRenderPass(commandBuffers[0]);
	if (vk.vkEndCommandBuffer(commandBuffers[0]) != VK_SUCCESS) {
		throw DevaException("failed to record command buffer!");
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
	submitInfo.pCommandBuffers = &commandBuffers[0];
	VkSemaphore signalSemaphores[] = { renderFinishedSemaphore };
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = signalSemaphores;
	auto & queues = main_device.getQueuesOfFamily(VK_QUEUE_GRAPHICS_BIT);
	if (queues.size() == 0)
		throw DevaException("0 queues");

	VkQueue q = queues[0].handle();

	vk.vkWaitForFences(device, 1, &fence, VK_TRUE, 1000);
	vk.vkResetFences(device, 1, &fence);

	if (vk.vkQueueSubmit(q, 1, &submitInfo, fence) != VK_SUCCESS) {
		throw DevaExternalFailureException("Vulkan", "Failed to submit draw command buffer!");
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

	i++;
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
		vkd.vkDestroyRenderPass(dev, renderPass, nullptr);
		imageAvailableSemaphore.replace();
		renderFinishedSemaphore.replace();
		vkd.vkDestroyFence(dev, fence, nullptr);
		vkd.vkDestroySwapchainKHR(dev, this->swapchain.handle, nullptr);
		this->surface.replace();
		for (auto i : swapchain.framebuffers) {
			vkd.vkDestroyFramebuffer(dev, i, nullptr);
		}
		/*for (auto i : swapchain.images) {
			vkd.vkDestroyImage(dev, i, nullptr);
		}*/
		for (auto i : swapchain.imageViews) {
			vkd.vkDestroyImageView(dev, i, nullptr);
		}

		for (auto &i : dsLayouts) {
			vkd.vkDestroyDescriptorSetLayout(dev, i.second.first, nullptr);
		}

		vkd.vkDestroyDescriptorPool(dev, dpoolManager->getHandle(), nullptr);

		auto leftover = bufmemIndex->clear();
		for (auto &i : leftover.first) {
			vkd.vkDestroyBuffer(dev, i.handle(), nullptr);
		}
		leftover.first.clear();
		for (auto &i : leftover.second) {
			vkd.vkFreeMemory(dev, i.handle(), nullptr);
		}
		leftover.second.clear();
		this->commandPool.replace();
		//this->dpoolManager->clear();
		vkd.vkDestroyPipelineLayout(dev, pipeline.getPipelineLayout(), nullptr);
		vkd.vkDestroyPipeline(dev, pipeline.getHandle(), nullptr);


		vki.vkDestroyDebugReportCallbackEXT(inst, callback, nullptr);
	}
}

void VulkanRenderer::loadDrawableObject(const SceneObjectID &id, const DrawableObject & object) {

	auto dev = main_device.handle();
	auto &vk = main_device.vk();

	auto &m = object.model;

	size_t mvpsize = 16 * sizeof(float);
	size_t vsize = m.vertexCount() * m.vertexSize();
	size_t isize = m.faceIndices().size() * sizeof(uint32_t);
	size_t datasize = vsize + isize + mvpsize;

	VulkanBufferMemoryIndex::BufID bufid(VulkanBufferMemoryIndex::BufID::NULL_ID);
	for (auto id : bufmemIndex->getUnmappedBuffers()) {
		auto &buf = bufmemIndex->getBuffer(id);
		if (buf.size() >= datasize) {
			bufid = id;
			break;
		}
	}

	if (bufid == Uuid::NULL_ID) {
		bufid = bufmemIndex->addBuffer(VulkanBuffer::create(main_device, 0, datasize, VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_SHARING_MODE_EXCLUSIVE));
	}

	auto &buf = bufmemIndex->getBuffer(bufid);

	VulkanBufferMemoryIndex::MemID memid = Uuid::NULL_ID;

	auto memories = bufmemIndex->getUnmappedMemoryBlocks();
	for (auto id : memories) {
		auto &mem = bufmemIndex->getMemory(id);
		if (Vulkan::vulkanBufferCompatibleWithMemory(buf, mem)) {
			memid = id;
			break;
		}
	}
	if (memid == Uuid::NULL_ID) {
		memid = bufmemIndex->addMemory(VulkanMemory::forBuffer(buf, main_device, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT));
	}

	auto &mem = bufmemIndex->getMemory(memid);
	bufmemIndex->bindBufferMemory(bufid, memid, main_device, 0);

	void* memory = nullptr;
	VkDeviceSize offset = mvpsize;
	vk.vkMapMemory(dev, mem.handle(), offset, vsize, 0, &memory);
	memcpy(memory, m.vertexData().data(), vsize);
	vk.vkUnmapMemory(dev, mem.handle());

	offset = offset + vsize;
	vk.vkMapMemory(dev, mem.handle(), offset, isize, 0, &memory);
	memcpy(memory, m.faceIndices().data(), isize);
	vk.vkUnmapMemory(dev, mem.handle());

	VkDescriptorSet dset = dpoolManager->allocateDescriptorSets({ dsLayouts.begin()->second.first }, 1)[0];
	VkDescriptorBufferInfo dbufinfo;
	dbufinfo.buffer = buf.handle();
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

	VulkanRenderObject::Offsets offsets;
	offsets.mvp = 0;
	offsets.vertex = mvpsize;
	offsets.index = vsize + mvpsize;

	renderObjects.insert({ id, VulkanRenderObject(bufid, static_cast<uint32_t>(m.faceIndices().size()), offsets, dset)});
}

std::shared_ptr<Scene> VulkanRenderer::render(std::shared_ptr<Scene> scene)
{
	auto dev = this->main_device.handle();
	auto &vk = this->main_device.vk();

	for (auto &robj : renderObjects) {
		bufmemIndex->removeBuffer(robj.second.buffer(), true);
	}
	bufmemIndex->purge();

	if (currentScene) ::unregisterObserver(*currentScene, *sceneListener);
	auto oldScene = currentScene;
	currentScene = scene;
	::registerObserver(*currentScene, *sceneListener);

	auto &objs = currentScene->getAllObjectIDs();
	GuidGenerator ggen;
	for (auto &object : objs) {
		loadDrawableObject(object, currentScene->getObject(object));
	}

	return oldScene;
}

void VulkanRenderer::unloadModel(const SceneObjectID &id) {

	auto dev = main_device.handle();
	auto &vk = main_device.vk();
	//vk.vkWaitForFences(dev, 1, &fence, VK_TRUE, 100);

	auto obj = renderObjects.find(id);
	if (obj == renderObjects.end()) {
		throw DevaInvalidArgumentException(strformat("Object ID {} does not exist in renderer", (std::string)id));
	}

	VulkanRenderObject &vro = obj->second;

	bufmemIndex->removeBuffer(vro.buffer(), false);
	renderObjects.erase(obj);
}

void VulkanRenderer::updateModelMVP(const SceneObjectID &id, const mat4 &mvp) {
	auto dev = main_device.handle();
	auto &vk = main_device.vk();

	auto obji = renderObjects.find(id);
	if (obji == renderObjects.end()) {
		throw DevaInvalidArgumentException(strformat("Object ID {} does not exist in renderer", (std::string)id));
	}
	auto &obj = obji->second;

	auto &mem = bufmemIndex->getMemory(bufmemIndex->getBufferMemory(obj.buffer()));

	void* memory = nullptr;

	vk.vkWaitForFences(dev, 1, &fence, VK_TRUE, 100);
	vk.vkMapMemory(dev, mem.handle(), obj.offsets().mvp, sizeof(float) * 16, 0, &memory);
	memcpy(memory, mvp.asBytes().data(), sizeof(float) * 16);
	vk.vkUnmapMemory(dev, mem.handle());
}

void VulkanRenderer::ImplSceneUpdateListener::onNewObject(const Scene &scene, const SceneObjectID &objectID, const DrawableObject& object) {
	renderer.loadDrawableObject(objectID, object);
}

void VulkanRenderer::ImplSceneUpdateListener::onObjectRemoved(const Scene &scene, const SceneObjectID &objectID, const DrawableObject &object) {
	renderer.unloadModel(objectID);
}

void VulkanRenderer::ImplSceneUpdateListener::onObjectUpdated(const Scene &scene, const SceneObjectID &objectID, const DrawableObject &object) {
	renderer.updateModelMVP(objectID, scene.getObjectTransform(objectID));
}