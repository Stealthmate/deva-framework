#include "VulkanDescriptorSetLayout.hpp"

#include "VulkanDevice.hpp"

using namespace DevaFramework;

VulkanDescriptorSetLayout Vulkan::createDescriptorSetLayout(
	const DevaFramework::VulkanDevice &device,
	const std::vector<VkDescriptorSetLayoutBinding> &bindings,
	VkDescriptorSetLayoutCreateFlags flags) {

	auto dev = device.handle;
	auto &vk = device.vk;

	VkDescriptorSetLayoutCreateInfo cinfo;
	cinfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	cinfo.pNext = nullptr;
	cinfo.flags = flags;
	cinfo.bindingCount = static_cast<uint32_t>(bindings.size());
	cinfo.pBindings = bindings.data();

	VulkanDescriptorSetLayout layout;

	if (vk.vkCreateDescriptorSetLayout(dev, &cinfo, nullptr, &layout.handle) != VK_SUCCESS) {
		throw DevaException("Could not create descriptor set layout");
	}

	for (auto i : bindings) {
		VulkanDescriptorSetLayout::Binding binfo;
		binfo.descriptorType = i.descriptorType;
		binfo.descriptorCount = i.descriptorCount;
		layout.bindings.insert({ i.binding, binfo });
	}

	return layout;

}