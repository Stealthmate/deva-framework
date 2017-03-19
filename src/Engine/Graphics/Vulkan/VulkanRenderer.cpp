#define DEVA_DO_NOT_DEFINE_UUID_OPERATORS_IN_STD

#define NOMINMAX
#include "VulkanRenderer.hpp"

#include "VulkanPipelineBuilder.hpp"

#include <DevaFramework\Graphics\Vulkan\Common.hpp>
#include <DevaFramework\Graphics\Vulkan\VulkanCommandPool.hpp>
#include <DevaFramework\Graphics\Vulkan\VulkanBuffer.hpp>
#include <DevaFramework\Graphics\Vulkan\VulkanMemory.hpp>
#include <DevaFramework\Util\Time.hpp>
#include <limits>
#include <unordered_set>

using namespace DevaFramework;
using namespace DevaEngine;

namespace DevaEngine {

	class VulkanRenderer::BufferMemoryIndex {

		bool needsPurge = false;

		std::unordered_set<Uuid> bufferIDs;
		std::unordered_set<Uuid> memoryIDs;
		std::unordered_map<Uuid, std::unique_ptr<VulkanBuffer>> bufferIDMap;
		std::unordered_map<Uuid, std::unique_ptr<VulkanMemory>> memoryIDMap;
		std::unordered_map<Uuid, Uuid> bufferToMemoryMap;
		std::unordered_map<Uuid, std::unordered_set<Uuid>> memoryToBuffersMap;

		std::unique_ptr<VulkanBuffer> eraseBuffer(const Uuid &id) {
			bufferIDs.erase(id);
			std::unique_ptr<VulkanBuffer> buf;

			auto i = bufferIDMap.find(id);
			if (i != bufferIDMap.end()) {
				buf = std::move(i->second);
				bufferIDMap.erase(i);
			}

			return buf;
		}

		std::unique_ptr<VulkanMemory> eraseMemory(const Uuid &id) {
			memoryIDs.erase(id);
			std::unique_ptr<VulkanMemory> mem;

			auto i = memoryIDMap.find(id);
			if (i != memoryIDMap.end()) {
				mem = std::move(i->second);
				memoryIDMap.erase(i);
			}

			return mem;
		}

	public:

#define BUFFER_NOT_FOUND(id) DevaInvalidArgumentException(strformat("Buffer with ID: {} does not exist in index", id.str()));
#define MEMORY_NOT_FOUND(id) DevaInvalidArgumentException(strformat("Memory with ID: {} does not exist in index", id.str()));

		Uuid addBuffer(std::unique_ptr<VulkanBuffer> buffer, const Uuid &memory) {

			auto iMem = memoryIDs.find(memory);
			if (iMem == memoryIDs.end()) {
				throw MEMORY_NOT_FOUND(memory);
			}

			Uuid id;
			while (bufferIDs.find(id) != bufferIDs.end()) id = Uuid();

			bufferIDs.insert(id);
			bufferIDMap.insert({ id, std::move(buffer) });
			bufferToMemoryMap.insert({id, memory});
			memoryToBuffersMap.find(memory)->second.insert(id);

			return id;
		}
		VulkanBuffer& getBuffer(const Uuid &id) {
			auto i = bufferIDs.find(id);
			if (i == bufferIDs.end()) {
				throw BUFFER_NOT_FOUND(id);
			}

			return *bufferIDMap.find(id)->second;
		}
		const VulkanBuffer& getBuffer(const Uuid &id) const {
			auto i = bufferIDs.find(id);
			if (i == bufferIDs.end()) {
				throw BUFFER_NOT_FOUND(id);
			}

			return *bufferIDMap.find(id)->second;
		}

		Uuid getBufferMemory(const Uuid &bufID) {
			auto i = bufferIDs.find(bufID);
			if (i == bufferIDs.end()) {
				throw BUFFER_NOT_FOUND(bufID);
			}

			return bufferToMemoryMap.find(bufID)->second;
		}

		void bindBufferMemory(const Uuid &bufID, const Uuid &memID, const VulkanDevice &dev, VkDeviceSize offset = 0) {

			auto iBuf = bufferIDMap.find(bufID);
			if (iBuf == bufferIDMap.end()) {
				throw BUFFER_NOT_FOUND(bufID);
			}
			auto iMem = memoryIDMap.find(memID);
			if (iMem == memoryIDMap.end()) {
				throw MEMORY_NOT_FOUND(memID);
			}

			auto iMappedMem = bufferToMemoryMap.find(iBuf->first);
			if (iMappedMem != bufferToMemoryMap.end()) {
				throw DevaInvalidArgumentException(strformat("Buffer {} has already been mapped to memory {}", bufID.str(), iMappedMem->second.str()));
			}

			auto device = dev.handle();
			auto &vk = dev.vk();
			VkResult result = vk.vkBindBufferMemory(device, iBuf->second->handle(), iMem->second->handle(), offset);
			if (result != VK_SUCCESS) {
				throw DevaExternalFailureException("Vulkan", strformat("Could not bind buffer handle {} to memory handle {}", strm(iBuf->second->handle()), strm(iMem->second->handle())));
			}

			bufferToMemoryMap.insert({ bufID, memID });

			auto iMemBufMap = memoryToBuffersMap.find(memID);
			iMemBufMap->second.insert(bufID);
		}

		Uuid addMemory(std::unique_ptr<VulkanMemory> memory) {
			Uuid id;
			while (memoryIDs.find(id) != memoryIDs.end()) id = Uuid();

			memoryIDs.insert(id);
			memoryIDMap.insert({ id, std::move(memory) });
			memoryToBuffersMap.insert({ id, {} });

			return id;
		}
		VulkanMemory& getMemory(const Uuid &id) {
			auto i = memoryIDs.find(id);
			if (i == memoryIDs.end()) {
				throw MEMORY_NOT_FOUND(id);
			}

			return *memoryIDMap.find(id)->second;
		}
		const VulkanMemory& getMemory(const Uuid &id) const {
			auto i = memoryIDs.find(id);
			if (i == memoryIDs.end()) {
				throw MEMORY_NOT_FOUND(id);
			}

			return *memoryIDMap.find(id)->second;
		}

		void removeBuffer(Uuid id, bool discardMemory) {
			auto iBuf = bufferIDs.find(id);
			if (iBuf == bufferIDs.end()) {
				throw BUFFER_NOT_FOUND(id);
			}

			auto iBufMem = bufferToMemoryMap.find(id);
			Uuid memID = iBufMem->second;

			auto iMemBuf = memoryToBuffersMap.find(memID);
			iMemBuf->second.erase(id);
			if (discardMemory && iMemBuf->second.size() == 0) {
				removeMemory(memID);
			}
			bufferToMemoryMap.erase(iBufMem);
			bufferIDs.erase(iBuf);
			needsPurge = true;
		}

		void removeMemory(Uuid id) {
			auto iMem = memoryIDs.find(id);
			if (iMem == memoryIDs.end()) {
				throw MEMORY_NOT_FOUND(id);
			}

			auto iMemBuf = memoryToBuffersMap.find(id);

			if (iMemBuf != memoryToBuffersMap.end() && iMemBuf->second.size() > 0) {
				throw DevaInvalidArgumentException(strformat("Memory {} is still bound to {} buffers", id.str(), iMemBuf->second.size()));
			}

			memoryToBuffersMap.erase(iMemBuf);
			memoryIDs.erase(id);
			needsPurge = true;
		}

		std::pair<std::vector<std::unique_ptr<VulkanBuffer>>, std::vector<std::unique_ptr<VulkanMemory>>> purge() {
			
			if (!needsPurge) return{};

			std::pair<std::vector<std::unique_ptr<VulkanBuffer>>, std::vector<std::unique_ptr<VulkanMemory>>> purged;

			auto i = bufferIDMap.begin();
			while (i != bufferIDMap.end()) {
				if (bufferIDs.find(i->first) == bufferIDs.end()) {
					purged.first.push_back(std::move(i->second));
					i = bufferIDMap.erase(i);
				}
				else {
					i++;
				}
			}

			auto j = memoryIDMap.begin();
			while (j != memoryIDMap.end()) {
				if (memoryIDs.find(j->first) == memoryIDs.end()) {
					purged.second.push_back(std::move(j->second));
					j = memoryIDMap.erase(j);
				}
				else {
					j++;
				}
			}
			needsPurge = false;

			//LOG.d(strformat("Purged {} buffers and {} memory blocks", purged.first.size(), purged.second.size()));

			return purged;
		}

		std::pair<std::vector<std::unique_ptr<VulkanBuffer>>, std::vector<std::unique_ptr<VulkanMemory>>> clear(bool discardResources) {
			std::pair<std::vector<std::unique_ptr<VulkanBuffer>>, std::vector<std::unique_ptr<VulkanMemory>>> purged = {};

			bufferIDs.clear();
			memoryIDs.clear();

			if (!discardResources) {
				purged = purge();
			}

			bufferIDMap.clear();
			bufferToMemoryMap.clear();
			memoryIDMap.clear();
			memoryToBuffersMap.clear();

			return purged;
		}
	};

	class ImplSceneUpdateListener : public Scene::SceneUpdateListener {
	public:

		VulkanRenderer& renderer;

		ImplSceneUpdateListener(VulkanRenderer& renderer) : renderer(renderer) {}

		virtual void onNewObject(const Scene::ObjectID &id, const DevaFramework::Model &object) override;
		virtual void onObjectUpdated(const Scene::ObjectID &id, const DevaFramework::Model &object) override;
		virtual void onObjectRemoved(const Scene::ObjectID &id, const DevaFramework::Model &object) override;
	};
}

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


VulkanRenderer::VulkanRenderer() :
	instance(VulkanInstance()),
	bufmemIndex(std::make_unique<BufferMemoryIndex>(BufferMemoryIndex())),
	sceneListener(std::make_shared<ImplSceneUpdateListener>(*this)) {}

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
VulkanRenderer::VulkanRenderer(const Window &wnd) : VulkanRenderer()
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

static std::vector<std::unique_ptr<VulkanBuffer>> buffers;
static std::vector<std::unique_ptr<VulkanMemory>> memories;

void VulkanRenderer::drawFrame()
{
	//if (drawn) return;
	auto &vk = main_device.vk();
	auto device = main_device.handle();

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
	vk.vkCmdBindPipeline(commandBuffers[0], VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);

	auto purged = bufmemIndex->purge();
	//for (auto &i : purged.first) buffers.push_back(std::move(i));
	for (auto &i : purged.second) memories.push_back(std::move(i));

	for (auto& object : renderObjects) {
		auto &obj = object.second;
		VulkanBuffer& buf = bufmemIndex->getBuffer(object.second.buffer());
		VkDeviceSize offsets[] = { 0 };
		VkBuffer handle = buf.handle();
		VkDeviceSize offsetIndex = obj.offsetIndex();
		vk.vkCmdBindVertexBuffers(commandBuffers[0], 0, 1, &handle, offsets);
		vk.vkCmdBindIndexBuffer(commandBuffers[0], handle, obj.offsetIndex(), VK_INDEX_TYPE_UINT32);
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
		bufmemIndex->clear(true);
		vkd.vkDestroyRenderPass(dev, renderPass, nullptr);
		imageAvailableSemaphore.replace();
		renderFinishedSemaphore.replace();
		vkd.vkDestroyFence(dev, fence, nullptr);
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

void VulkanRenderer::loadModel(const Scene::ObjectID &id, const Model &m) {

	auto dev = main_device.handle();
	auto &vk = main_device.vk();

	size_t datasize = (m.vertexCount() * m.vertexSize()) + (m.faceIndices().size() * sizeof(uint32_t));
	std::unique_ptr<VulkanMemory> memptr = nullptr;
	for (auto mem = memories.begin(); mem != memories.end(); mem++) {
		if (mem->get()->size() >= datasize) {
			memptr = std::move(*mem);
			memories.erase(mem);
			break;
		}
	}
	std::unique_ptr<VulkanBuffer> bufptr = nullptr;
	for (auto buf = buffers.begin(); buf != buffers.end(); buf++) {
		if (buf->get()->size() >= datasize) {
			bufptr = std::move(*buf);
			buffers.erase(buf);
			break;
		}
	}

	if(!bufptr) bufptr = std::make_unique<VulkanBuffer>(VulkanBuffer::create(main_device, 0, datasize, VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_SHARING_MODE_EXCLUSIVE));
	if(!memptr) memptr = std::make_unique<VulkanMemory>(VulkanMemory::forBuffer(*bufptr, main_device, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT));
	
	Uuid memID = bufmemIndex->addMemory(std::move(memptr));
	VulkanMemory &memory = bufmemIndex->getMemory(memID);
	vk.vkBindBufferMemory(dev, bufptr->handle(), memory.handle(), 0);
	Uuid bufID = bufmemIndex->addBuffer(std::move(bufptr), memID);
	VulkanBuffer &buf = bufmemIndex->getBuffer(bufID);

	void* mem;
	vk.vkMapMemory(dev, memory.handle(), 0, memory.size(), 0, &mem);
	memcpy(mem, m.vertexData().data(), m.vertexCount() * m.vertexSize());
	vk.vkUnmapMemory(dev, memory.handle());

	VkDeviceSize offset = (m.vertexCount() * m.vertexSize());
	vk.vkMapMemory(dev, memory.handle(), offset, m.faceIndices().size() * sizeof(uint32_t), 0, &mem);
	memcpy(mem, m.faceIndices().data(), m.faceIndices().size() * sizeof(uint32_t));
	vk.vkUnmapMemory(dev, memory.handle());

	mem = nullptr;

	renderObjects.insert({ id, VulkanRenderObject(bufID, offset, static_cast<uint32_t>(m.faceIndices().size())) });
}

std::shared_ptr<Scene> VulkanRenderer::render(std::shared_ptr<Scene> scene)
{
	auto dev = this->main_device.handle();
	auto &vk = this->main_device.vk();

	for (auto &robj : renderObjects) {
		bufmemIndex->removeBuffer(robj.second.buffer(), true);
	}
	bufmemIndex->purge();

	if (currentScene) currentScene->unregisterUpdateListener(sceneListener);
	auto oldScene = currentScene;
	currentScene = scene;
	currentScene->registerUpdateListener(sceneListener);

	auto &objs = currentScene->getAllObjects();
	GuidGenerator ggen;
	for (auto &object : objs) {
		loadModel(object.first, *object.second);
	}

	return oldScene;
}

void VulkanRenderer::unloadModel(const Scene::ObjectID &id) {

	auto dev = main_device.handle();
	auto &vk = main_device.vk();
	//vk.vkWaitForFences(dev, 1, &fence, VK_TRUE, 100);

	auto obj = renderObjects.find(id);
	if (obj == renderObjects.end()) {
		throw DevaInvalidArgumentException(strformat("Object ID {} does not exist in renderer", (std::string)id));
	}

	VulkanRenderObject &vro = obj->second;

	bufmemIndex->removeBuffer(vro.buffer(), true);
	renderObjects.erase(obj);
}

void ImplSceneUpdateListener::onNewObject(const Scene::ObjectID &objectID, const Model& object) {
	renderer.loadModel(objectID, object);
}

void ImplSceneUpdateListener::onObjectRemoved(const Scene::ObjectID &objectID, const Model &object) {
	renderer.unloadModel(objectID);
}

void ImplSceneUpdateListener::onObjectUpdated(const Scene::ObjectID &objectID, const Model &object) {

}