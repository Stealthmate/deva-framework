#define DEVA_DO_NOT_DEFINE_UUID_OPERATORS_IN_STD

#define NOMINMAX
#include "VulkanRenderAPI.hpp"
#include "../../Preferences.hpp"

#include "VulkanPipelineBuilder.hpp"
#include "VulkanBufferMemoryIndex.hpp"

#include <DevaFramework\Core\Uuid.hpp>

#include <DevaFramework\Graphics\Image.hpp>
#include <DevaFramework\Graphics\Mesh.hpp>
#include <DevaFramework\Graphics\Vulkan\Common.hpp>
#include <DevaFramework\Graphics\Vulkan\VulkanCommandPool.hpp>
#include <DevaFramework\Graphics\Vulkan\VulkanBuffer.hpp>
#include <DevaFramework\Graphics\Vulkan\VulkanMemory.hpp>

#include <DevaFramework\Util\Time.hpp>


#include"VulkanPresenter.hpp"

#include <limits>
#include <unordered_set>


using namespace DevaFramework;
using namespace DevaEngine;

using DevaFramework::Vulkan::LOG_VULKAN;

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

	const VkPhysicalDeviceFeatures EMPTY_FEATURES;

	const bool VULKAN_LOADED = false;

	std::pair<VkDescriptorSetLayout, VulkanDescriptorSetLayout> createLayout(
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

		VulkanDescriptorSetLayout layoutinfo;
		for (auto i : bindings) {
			VulkanDescriptorSetLayout::Binding binfo;
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
		layerPointers = DevaFramework::convertStringArrToPtrArr(layerStrings);
	}

	auto extensions = prefs.getPreference("vkextensions");
	std::vector<const char*> extensionPointers;
	std::vector<std::string> extensionStrings;
	if (extensions.has_value() && extensions.type() == typeid(std::vector<std::string>)) {
		extensionStrings = std::any_cast<std::vector<std::string>>(extensions);
		extensionPointers = DevaFramework::convertStringArrToPtrArr(extensionStrings);
	}

	VkInstanceCreateInfo instanceInfo(INSTANCE_CREATE_INFO);
	instanceInfo.enabledLayerCount = static_cast<uint32_t>(layerPointers.size());
	instanceInfo.ppEnabledLayerNames = layerPointers.data();
	instanceInfo.enabledExtensionCount = static_cast<uint32_t>(extensionPointers.size());
	instanceInfo.ppEnabledExtensionNames = extensionPointers.data();
	this->instance = DevaFramework::Vulkan::createInstance(instanceInfo);

	auto &vk = instance.vk;
	callback = DevaFramework::Vulkan::attachDebugCallback(instance, &debug, VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT);
	bufmemIndex = std::make_unique<VulkanBufferMemoryIndex>();
}

void VulkanRenderAPI::onSetupRenderTargetWindow(const Window &wnd) {
	presenter = std::make_unique<VulkanPresenter>(instance, wnd);

	main_device = presenter->device();
	renderQueue = presenter->queue();
	queueBuffer = VulkanQueueSubmitBuffer(renderQueue);

	createRenderPass();
	createFramebuffers();

	fence = DevaFramework::Vulkan::createFence(main_device, VK_FENCE_CREATE_SIGNALED_BIT);
	imageAvailableSemaphore = DevaFramework::Vulkan::createSemaphore(main_device);
	renderFinishedSemaphore = DevaFramework::Vulkan::createSemaphore(main_device);

	createPipeline();
}

void VulkanRenderAPI::createFramebuffers() {

	auto dev = main_device.handle;
	auto &vk = main_device.vk;

	auto swapchain = presenter->swapchain();
	framebuffers.resize(swapchain.imageViews.size());
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

		if (vk.vkCreateFramebuffer(dev, &framebufferInfo, nullptr, &framebuffers[i]) != VK_SUCCESS) {
			throw DevaException("failed to create framebuffer!");
		}
	}
}


void VulkanRenderAPI::onSetupRenderTargetImage(const Image &img) {
	throw DevaUnsupportedOperationException("Image rendering not supported yet");
}

void VulkanRenderAPI::createRenderPass()	 {
	VkAttachmentDescription colorAttachment = {};
	colorAttachment.format = presenter->swapchain().format;
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
		.outputExtent(presenter->swapchain().extent);

	auto &vk = main_device.vk;
	auto device = main_device.handle;

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
	plb.addDescriptorSetLayout(dslayout.first);
	descSetIndexMap.insert({ id, 0 });

	descPool = DevaFramework::Vulkan::createDescriptorPool(main_device, { dslayout.second }, 10);

	this->pipeline = plb.build(this->main_device);

	renderPassRecord.pipeline = pipeline.handle;
	renderPassRecord.renderArea = presenter->swapchain().extent;
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

void VulkanRenderAPI::drawScene() {
	auto &vk = main_device.vk;
	auto device = main_device.handle;

	VkResult res = vk.vkWaitForFences(device, 1, &fence, VK_TRUE, std::numeric_limits<uint32_t>::max());
	if (res != VK_SUCCESS) LOG.w("FENCE NOT COMPLETE " + strm(res));
	vk.vkResetFences(device, 1, &fence);

	vk.vkFreeCommandBuffers(device, commandPool.handle, 1, &commandBuffers[0].handle);
	commandBuffers[0] = DevaFramework::Vulkan::allocateCommandBuffer(main_device, commandPool, VK_COMMAND_BUFFER_LEVEL_PRIMARY);
	DevaFramework::Vulkan::beginCommandBuffer(main_device, commandBuffers[0].handle, VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT);

	uint32_t imageIndex = presenter->nextImageIndex(std::numeric_limits<uint64_t>::max(), imageAvailableSemaphore, VK_NULL_HANDLE);
	//vk.vkAcquireNextImageKHR(device, swapchain.handle, std::numeric_limits<uint64_t>::max(), imageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);

	renderPassRecord.framebuffer = framebuffers[imageIndex];

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

	presenter->present(renderQueue.handle, { renderFinishedSemaphore }, imageIndex);
	//DevaEngine::Vulkan::present(main_device, renderQueue.handle, { renderFinishedSemaphore }, { swapchain.handle }, { imageIndex });
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
		auto swapchain = presenter->swapchain();
		for (auto i : swapchain.imageViews) {
			vkd.vkDestroyImageView(dev, i, nullptr);
		}
		for (auto i : framebuffers) {
			vkd.vkDestroyFramebuffer(dev, i, nullptr);
		}
		vkd.vkDestroySwapchainKHR(dev, swapchain.handle, nullptr);

		for (auto &i : dsLayouts) {
			DevaFramework::Vulkan::destroyObject(main_device, i.second.second);
		}

		DevaFramework::Vulkan::destroyObject(main_device, descPool);

		auto leftover = bufmemIndex->clear();
		for (auto &i : leftover.first) {
			DevaFramework::Vulkan::destroyObject(main_device, i);
		}
		leftover.first.clear();
		for (auto &i : leftover.second) {
			DevaFramework::Vulkan::destroyObject(main_device, i);
		}
		leftover.second.clear();
		DevaFramework::Vulkan::destroyObject(main_device, commandPool);

		vkd.vkDestroyPipelineLayout(dev, pipeline.layout, nullptr);
		DevaFramework::Vulkan::destroyObject(main_device, pipeline);


		vki.vkDestroyDebugReportCallbackEXT(inst, callback, nullptr);

		DevaFramework::Vulkan::destroyObject(main_device);
		DevaFramework::Vulkan::destroyObject(instance);
	}
}

RenderObjectID VulkanRenderAPI::loadMesh(const Mesh &mesh) {
	auto dev = main_device.handle;
	auto &vk = main_device.vk;

	size_t mvpsize = 16 * sizeof(float);
	size_t vsize = mesh.vertexCount * mesh.vertexSize;
	size_t isize = mesh.faceCount * 3 * sizeof(uint32_t);
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
		bufid = bufmemIndex->addBuffer(
			DevaFramework::Vulkan::createBuffer(
				main_device, 0, datasize, 
				VK_BUFFER_USAGE_INDEX_BUFFER_BIT 
				| VK_BUFFER_USAGE_VERTEX_BUFFER_BIT 
				| VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, 
				VK_SHARING_MODE_EXCLUSIVE));
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
		memid = bufmemIndex->addMemory(
			DevaFramework::Vulkan::allocateMemoryForBuffer(
				main_device, buf, 
				VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT));
	}

	auto &mem = bufmemIndex->getMemory(memid);
	bufmemIndex->bindBufferMemory(bufid, memid, main_device, 0);

	void* memory = nullptr;
	VkDeviceSize offset = mvpsize;
	vk.vkMapMemory(dev, mem.handle, offset, vsize, 0, &memory);
	memcpy(memory, mesh.vertexData.data(), vsize);
	vk.vkUnmapMemory(dev, mem.handle);

	offset = offset + vsize;
	vk.vkMapMemory(dev, mem.handle, offset, isize, 0, &memory);
	memcpy(memory, mesh.vertexData.data() + mesh.faceDataOffset, isize);
	vk.vkUnmapMemory(dev, mem.handle);

	VulkanDescriptorSet dset = DevaFramework::Vulkan::allocateDescriptorSets(main_device, descPool, { dsLayouts.begin()->second.first }, 1)[0];
	VkDescriptorBufferInfo dbufinfo;
	dbufinfo.buffer = buf.handle;
	dbufinfo.offset = 0;
	dbufinfo.range = mvpsize;
	VkWriteDescriptorSet descriptorWrite = {};
	descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	descriptorWrite.dstSet = dset.handle;
	descriptorWrite.dstBinding = 0;
	descriptorWrite.dstArrayElement = 0;
	descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	descriptorWrite.descriptorCount = 1;
	descriptorWrite.pBufferInfo = &dbufinfo;
	descriptorWrite.pImageInfo = nullptr; // Optional
	descriptorWrite.pTexelBufferView = nullptr; // Optional
	vk.vkUpdateDescriptorSets(dev, 1, &descriptorWrite, 0, nullptr);

	VulkanMesh vmesh;

	vmesh.vertexBuffers = { buf.handle };
	vmesh.vertexOffsets = { mvpsize };

	vmesh.indexBuffer = buf.handle;
	vmesh.indexOffset = vsize + mvpsize;
	vmesh.indexCount = static_cast<uint32_t>(mesh.faceCount * 3);
	vmesh.indexType = VK_INDEX_TYPE_UINT32;
	vmesh.firstIndex = 0;

	vmesh.pipelineLayout = pipeline.layout;
	vmesh.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;

	vmesh.mvpBuffer = buf.handle;
	vmesh.mvpOffset = 0;
	vmesh.descriptorSets = { dset.handle };

	vmesh.firstInstance = 0;
	vmesh.instanceCount = 1;
	vmesh.vertexOffset = 0;

	VulkanMeshResources vmr;
	vmr.indexBuffer = bufid;
	vmr.mvpBuffer = bufid;
	vmr.vertexBuffers = { bufid };
	vmr.descSets = { dset };

	renderPassRecord.objs.push_back(vmesh);
	vmr.index = renderPassRecord.objs.size() - 1;

	RenderObjectID id;

	meshMap.insert({ id,{ vmesh, vmr } });

	return id;
}

RenderObjectID VulkanRenderAPI::loadTexture(const Image &tex) {
	auto dev = this->main_device.handle;
	auto vk = this->main_device.vk;

	size_t imageSize = tex.data.size();
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
	memcpy(mem, tex.data.data(), imageSize);
	vk.vkUnmapMemory(dev, bufmemIndex->getMemory(memid).handle);

	VulkanImage image;

	VkImageCreateInfo imageInfo = {};
	imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	imageInfo.imageType = VK_IMAGE_TYPE_2D;
	imageInfo.extent.width = static_cast<uint32_t>(tex.width);
	imageInfo.extent.height = static_cast<uint32_t>(tex.height);
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
		tex.width,
		tex.height,
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

void VulkanRenderAPI::unloadMesh(const RenderObjectID &id) {
	auto dev = main_device.handle;
	auto &vk = main_device.vk;

	vk.vkWaitForFences(dev, 1, &fence, VK_TRUE, 100000);

	auto i = meshMap.find(id);
	if (i == meshMap.end()) {
		throw DevaInvalidArgumentException(strformat("MeshID {} does not exist in renderer", (std::string)id));
	}

	auto &mesh = i->second.first;
	auto &vrm = i->second.second;

	std::unordered_set<DevaFramework::Vulkan::VulkanBufferID> bufids;
	bufids.insert(vrm.indexBuffer);
	bufids.insert(vrm.mvpBuffer);
	bufids.insert(vrm.vertexBuffers.begin(), vrm.vertexBuffers.end());
	for (auto &i : bufids) {
		bufmemIndex->removeBuffer(i, false);
	}

	//bugged
	DevaFramework::Vulkan::freeDescriptorSets(main_device, vrm.descSets);

	auto irp = renderPassRecord.objs.begin();
	std::advance(irp, vrm.index);
	renderPassRecord.objs.erase(irp);
	meshMap.erase(i);
}

void VulkanRenderAPI::unloadTexture(const RenderObjectID &id) {
	//TODO
}

void VulkanRenderAPI::bindMeshTexture(const RenderObjectID &meshid, const RenderObjectID &texid) {
	//TODO
}

void VulkanRenderAPI::unbindMeshTexture(const RenderObjectID &meshid, const RenderObjectID &texid) {
	//TODO
}

void VulkanRenderAPI::setMeshMVP(const RenderObjectID &meshid, const mat4 &mvp) {
	auto dev = main_device.handle;
	auto &vk = main_device.vk;

	auto meshi = meshMap.find(meshid);
	if (meshi == meshMap.end()) {
		throw DevaInvalidArgumentException(strformat("Mesh ID {} does not exist in renderer", (std::string)meshid));
	}
	auto &obj = meshi->second;

	auto &mem = bufmemIndex->getMemory(bufmemIndex->getBufferMemory(obj.second.mvpBuffer));

	void* memory = nullptr;

	vk.vkWaitForFences(dev, 1, &fence, VK_TRUE, 100);
	vk.vkMapMemory(dev, mem.handle, obj.first.mvpOffset, sizeof(float) * 16, 0, &memory);
	auto rawmvp = mvp.rawData();
	memcpy(memory, (const unsigned char*)rawmvp.first, rawmvp.second * sizeof(float));
	vk.vkUnmapMemory(dev, mem.handle);

	VkBufferCopy bc;
	bc.srcOffset = obj.first.mvpOffset;
	bc.size = sizeof(float) * 16;
	bc.dstOffset = obj.first.mvpOffset;
	//TODO
}

void UpdateStager::stageUpdate(
	const DevaFramework::VulkanDevice &device,
	void * srcData,
	VkDeviceSize dataSize,
	VkBuffer dst,
	VkDeviceSize dstOffset
) {

	if (dataSize > usedCap)
		throw DevaException("Attempt to write beyond buffer size");

	auto dev = device.handle;
	auto &vk = device.vk;

	void * mem = nullptr;
	vk.vkMapMemory(dev, memory, usedCap, dataSize, 0, &mem);
	std::memcpy((byte_t*)mem, (byte_t*)srcData, dataSize);
	vk.vkUnmapMemory(dev, memory);
	mem = nullptr;

	usedCap += dataSize;

	PrebufInfo info;
	info.srcOffset = usedCap - dataSize;
	info.size = dataSize;
	info.dst = dst;
	info.dstOffset = dstOffset;

	queue.push_back(info);
}

void UpdateStager::recordFlush(const VulkanDevice &device, VkCommandBuffer buf) {
	auto dev = device.handle;
	auto &vk = device.vk;

	for (auto &u : queue) {

		VkBufferCopy bc;
		bc.srcOffset = u.srcOffset;
		bc.dstOffset = u.dstOffset;
		bc.size = u.size;

		vk.vkCmdCopyBuffer(buf, prebuffer, u.dst, 1, &bc);
	}
}