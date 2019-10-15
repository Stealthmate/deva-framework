#include "VulkanPresenter.hpp"

#include <DevaFramework\Graphics\Vulkan\Common.hpp>
#include <DevaFramework\Util\Common.hpp>

#include "VulkanSwapchain.hpp"
#include<DevaFramework\Graphics\Vulkan\VulkanDeviceQueue.hpp>

using namespace DevaFramework;
using namespace DevaEngine;

namespace {
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

	const VkPhysicalDeviceFeatures EMPTY_FEATURES;
	const char * DEVICE_EXTENSIONS[] =
	{
		VK_KHR_SWAPCHAIN_EXTENSION_NAME,
	};
	VulkanDevice createLogicalDevice(
		const VulkanInstance& instance,
		const VulkanPhysicalDevice &pdev,
		uint32_t queueIndex,
		const std::vector<std::string> &extensions = {},
		VkPhysicalDeviceFeatures features = EMPTY_FEATURES)
	{
		std::vector<float> priorities = { 1.0f };
		VkDeviceQueueCreateInfo q_cinfo;
		q_cinfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		q_cinfo.pNext = nullptr;
		q_cinfo.queueCount = 1;
		q_cinfo.queueFamilyIndex = queueIndex;
		q_cinfo.pQueuePriorities = priorities.data();
		q_cinfo.flags = 0;
		for (auto ext : extensions)
		{
			if (!DevaFramework::Vulkan::doesDeviceSupportExtension(pdev, ext.c_str()))
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
		auto extptrs = convertStringArrToPtrArr(extensions);
		dev_cinfo.enabledExtensionCount = extptrs.size();
		dev_cinfo.ppEnabledExtensionNames = extptrs.data();
		features.fillModeNonSolid = VK_TRUE;
		if (pdev.features.fillModeNonSolid) dev_cinfo.pEnabledFeatures = &features;

		return DevaFramework::Vulkan::createDevice(instance, pdev, dev_cinfo);
	}

}

VulkanQueue VulkanPresenter::queue() const {
	return mQueue;
}

VulkanSwapchain VulkanPresenter::swapchain() const {
	return mSwapchain;
}

VulkanDevice VulkanPresenter::device() const {
	return mDev;
}

uint32_t VulkanPresenter::nextImageIndex(uint64_t timeout, VkSemaphore sem, VkFence fence) {
	uint32_t imageIndex;
	mDev.vk.vkAcquireNextImageKHR(mDev.handle, mSwapchain.handle, timeout, sem, fence, &imageIndex);
	return imageIndex;
}

VulkanPresenter::VulkanPresenter(const VulkanInstance &instance, const Window &wnd) {

	VkSurfaceKHR surface = DevaFramework::Vulkan::createSurfaceForWindow(instance, wnd);

	VulkanPhysicalDevice gpu;
	uint32_t queueIndex = 0;
	if (!::pickGPU(instance, surface, &gpu, &queueIndex)) throw DevaException("Could not find suitable GPU and/or queue");
	mDev = ::createLogicalDevice(instance, gpu, queueIndex, { VK_KHR_SWAPCHAIN_EXTENSION_NAME });
	ENGINE_LOG.v(strformat("Using GPU: {}", gpu.properties.deviceName));
	this->mQueue = DevaFramework::Vulkan::getDeviceQueue(mDev, queueIndex, 0);
	auto surfaceprops = DevaFramework::Vulkan::getSurfaceProperties(instance, gpu, surface);

	uint32_t formatCount = static_cast<uint32_t>(surfaceprops.formats.size());
	if (formatCount == 1 && surfaceprops.formats[0].format == VK_FORMAT_UNDEFINED)
		mFormat = VK_FORMAT_B8G8R8A8_UNORM;
	else {
		if (formatCount == 0)
			throw DevaExternalFailureException("Vulkan", "Device has no surface formats!");
		mFormat = surfaceprops.formats[0].format;
	}
	VkColorSpaceKHR colorSpace = surfaceprops.formats[0].colorSpace;

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
		queueIndex
	};

	VkSwapchainCreateInfoKHR swapchainCreateInfo = {};
	swapchainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	swapchainCreateInfo.surface = surface;
	swapchainCreateInfo.minImageCount = imageCount;
	swapchainCreateInfo.imageFormat = mFormat;
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

	mSwapchain = DevaEngine::Vulkan::createSwapchain(mDev, swapchainCreateInfo);
}

void VulkanPresenter::present(VkQueue queue,
	const std::vector<VkSemaphore> &waitSemaphores,
	uint32_t imageIndex) {
	DevaEngine::Vulkan::present(mDev, queue, waitSemaphores, { mSwapchain.handle }, { imageIndex });
}

void DevaEngine::Vulkan::present(
	const DevaFramework::VulkanDevice &dev,
	VkQueue queue,
	const std::vector<VkSemaphore> &waitSemaphores,
	const std::vector<VkSwapchainKHR> &swapchains,
	const std::vector<uint32_t> &imageIndices
) {
	
	VkPresentInfoKHR info = {};
	info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

	info.waitSemaphoreCount = static_cast<uint32_t>(waitSemaphores.size());
	info.pWaitSemaphores = waitSemaphores.data();
	info.swapchainCount = static_cast<uint32_t>(swapchains.size());
	info.pSwapchains = swapchains.data();
	info.pImageIndices = imageIndices.data();
	info.pResults = nullptr; // Optional

	dev.vk.vkQueuePresentKHR(queue, &info);
}