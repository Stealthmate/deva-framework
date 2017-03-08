#include "VulkanInstance.hpp"

using namespace DevaFramework;

namespace
{
	const VkApplicationInfo DEFAULT_APPLICATION_INFO =
	{
		VK_STRUCTURE_TYPE_APPLICATION_INFO,
		NULL,
		"Vulkan Application",
		VK_MAKE_VERSION(1, 0, 0),
		"Deva Engine",
		VK_MAKE_VERSION(1, 0, 0),
		VK_MAKE_VERSION(1, 0, 13)
	};

	const VkInstanceCreateInfo DEFAULT_INSTANCE_CREATE_INFO =
	{
		VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		NULL,
		0,
		&DEFAULT_APPLICATION_INFO,
		0,
		NULL,
		0,
		NULL
	};
}

#define ERRCHK if( result != VK_SUCCESS ) throw DevaException("DevaFramework::VulkanInstance failed because of Vulkan. Check logs for more info.");

VulkanInstance VulkanInstance::create()
{
	return create(DEFAULT_INSTANCE_CREATE_INFO);
}

VulkanInstance VulkanInstance::create(const VkInstanceCreateInfo &info)
{
	LOG_VULKAN.v("Creating VulkanInstance...");
	VkInstance instance_handle;

	if (!internal::vkCreateInstance)
		throw DevaProgrammerErrorException("Vulkan not initialized (did you call DevaFramework::loadVulkan()?)");

	std::vector<std::string> extensions;
	for (uint32_t i = 0;i <= info.enabledExtensionCount - 1;i++)
	{
		extensions.push_back(*(info.ppEnabledExtensionNames + i));
		if (!vulkanInstanceExtensionAvailable(extensions[i]))
			throw DevaExternalFailureException("Vulkan", "Could not create VkInstance - extension " + extensions[i] + " not supported by system.");
	}

	auto result = internal::vkCreateInstance(&info, NULL, &instance_handle);
	ERRCHK;

	return VulkanInstance(instance_handle);
}

void VulkanInstance::populatePDeviceList()
{
	VkResult result;

	LOG_VULKAN.v("Enumerating physical devices (count)...");
	uint32_t device_count = 0;
	result = mVk.vkEnumeratePhysicalDevices(mHandle, &device_count, NULL);
	ERRCHK;

	if (device_count == 0) {
		throw DevaException(std::string("No physical devices available."));
	}

	LOG_VULKAN.v("System has " + strm(device_count) + " devices.");

	LOG_VULKAN.v("Enumerating physical devices (mHandles)...");
	std::vector<VkPhysicalDevice> deviceHandles(device_count);
	result = mVk.vkEnumeratePhysicalDevices(mHandle, &device_count, &deviceHandles[0]);
	ERRCHK;

	for (uint32_t i = 0; i <= device_count - 1; i++)
	{
		this->physical_devices.push_back(VulkanPhysicalDeviceWrapper::fromHandle(*this, deviceHandles[i]));
	}
}


VulkanInstance::VulkanInstance(VkInstance handle) : mHandle(handle)
{
	LOG_VULKAN.v("Loading instance-local functions...");
	mVk = VulkanInstanceFunctionSet::load(mHandle);

	populatePDeviceList();

	LOG_VULKAN.i("Successfully initialized VulkanInstance");
}

VulkanInstance::VulkanInstance() : mHandle(VK_NULL_HANDLE) {}

VulkanInstance::VulkanInstance(VulkanInstance &&instance) 
	: mHandle(instance.mHandle), mVk(instance.mVk), physical_devices(instance.physical_devices)
{
	instance.mHandle = VK_NULL_HANDLE;
	instance.physical_devices.clear();
}

VulkanInstance& VulkanInstance::operator=(VulkanInstance &&instance)
{
	this->mHandle = instance.mHandle;
	instance.mHandle = VK_NULL_HANDLE;

	this->physical_devices = instance.physical_devices;
	instance.physical_devices.clear();

	mVk = instance.mVk;

	return *this;
}


VulkanInstance::~VulkanInstance()
{
	destroy();
}

VkInstance VulkanInstance::handle() const
{
	return this->mHandle;
}

const VulkanInstanceFunctionSet& VulkanInstance::vk() const
{
	return mVk;
}

std::vector<VulkanPhysicalDeviceWrapper> VulkanInstance::getPhysicalDevices() const
{
	return physical_devices;
}

void VulkanInstance::destroy()
{
	if (mHandle != VK_NULL_HANDLE) mVk.vkDestroyInstance(mHandle, NULL);
}