#include "VulkanInstance.hpp"

using namespace DevaFramework;


#define ERRCHK if( result != VK_SUCCESS ) throw DevaException("DevaFramework::VulkanInstance failed because of Vulkan. Check logs for more info.");

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

	std::vector<VulkanPhysicalDeviceTraits> getPhysicalDeviceTraits(const VulkanInstance &inst) {
		VkResult result;

		VkInstance in = inst.handle();
		auto& vk = inst.vk();

		LOG_VULKAN.v("Enumerating physical devices (count)...");
		uint32_t device_count = 0;
		result = vk.vkEnumeratePhysicalDevices(in, &device_count, NULL);
		ERRCHK;

		if (device_count == 0) {
			throw DevaException(std::string("No physical devices available."));
		}

		LOG_VULKAN.v("System has " + strf(device_count) + " devices.");

		LOG_VULKAN.v("Enumerating physical devices (mHandles)...");
		std::vector<VkPhysicalDevice> deviceHandles(device_count);
		result = vk.vkEnumeratePhysicalDevices(in, &device_count, &deviceHandles[0]);
		ERRCHK;

		std::vector<VulkanPhysicalDeviceTraits> pdevs;
		for (uint32_t i = 0; i <= device_count - 1; i++)
		{
			pdevs.emplace_back(VulkanPhysicalDeviceTraits::forDevice(inst, deviceHandles[i]));
		}

		return pdevs;
	}
}

VulkanInstance VulkanInstance::createDefault()
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

VulkanInstance::VulkanInstance() noexcept {}

VulkanInstance::VulkanInstance(VkInstance handle) : VulkanObject(handle, {})
{
	LOG_VULKAN.v("Loading instance-local functions...");
	mVk = VulkanInstanceFunctionSet::load(mHandle);

	mInfo.physicalDevices = getPhysicalDeviceTraits(*this);

	LOG_VULKAN.i("Successfully initialized VulkanInstance");
}

VulkanInstance::VulkanInstance(VulkanInstance &&instance) noexcept
	: VulkanObject(std::move(instance)),
	mVk(instance.mVk)
{
	instance.mVk = VulkanInstanceFunctionSet();
}

VulkanInstance& VulkanInstance::operator=(VulkanInstance &&instance) noexcept
{
	swap(instance);

	return *this;
}

void VulkanInstance::swap(VulkanInstance &rhs) {
	using std::swap;
	VulkanObject::swap(rhs);
	swap(mVk, rhs.mVk);
}

void Vulkan::destroyObject(VulkanInstance &instance) {
	instance.vk().vkDestroyInstance(instance.handle(), nullptr);
	instance.reset();
}

void DevaFramework::swap(VulkanInstance &lhs, VulkanInstance &rhs) {
	lhs.swap(rhs);
}