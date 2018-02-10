#include "VulkanDescriptorSet.hpp"

#include "VulkanDevice.hpp"

using namespace DevaFramework;

void Vulkan::destroyObject(
	const VulkanDevice &dev,
	VulkanDescriptorSetLayout &obj) {
	dev.vk.vkDestroyDescriptorSetLayout(dev.handle, obj.handle, nullptr);
	obj.handle = VK_NULL_HANDLE;
}

void Vulkan::destroyObject(
	const VulkanDevice &dev,
	VulkanDescriptorPool &obj) {
	dev.vk.vkDestroyDescriptorPool(dev.handle, obj.handle, nullptr);
	obj.handle = VK_NULL_HANDLE;
}


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

VulkanDescriptorPool Vulkan::createDescriptorPool(
	const VulkanDevice &device,
	const std::vector<VulkanDescriptorSetLayout> &layouts,
	uint32_t maxSets) {

	auto dev = device.handle;
	auto &vk = device.vk;


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
	cinfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
	cinfo.poolSizeCount = static_cast<uint32_t>(sizes.size());
	cinfo.pPoolSizes = sizes.data();
	cinfo.maxSets = maxSets;
	
	VulkanDescriptorPool pool;

	if (vk.vkCreateDescriptorPool(dev, &cinfo, nullptr, &pool.handle) != VK_SUCCESS)
		throw DevaException("Could not create descriptor pool");

	pool.supportedLayouts = layouts;

	return pool;
}

std::vector<VulkanDescriptorSet> Vulkan::allocateDescriptorSets(
	const VulkanDevice &device,
	const VulkanDescriptorPool &pool,
	const std::vector<VkDescriptorSetLayout> &layouts,
	size_t count) {

	auto dev = device.handle;
	auto &vk = device.vk;

	VkDescriptorSetAllocateInfo info;
	info.descriptorPool = pool.handle;
	info.descriptorSetCount = static_cast<uint32_t>(count);
	info.pNext = nullptr;
	info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	info.pSetLayouts = layouts.data();

	std::vector<VkDescriptorSet> sets(count);
	sets.resize(count);
	if (device.vk.vkAllocateDescriptorSets(device.handle, &info, sets.data()) != VK_SUCCESS)
		throw DevaException("Could not allocated descriptor sets");

	std::vector<VulkanDescriptorSet> wrappedSets;
	for (auto s : sets) {
		wrappedSets.push_back({ s, pool.handle });
	}

	return wrappedSets;
}

void Vulkan::freeDescriptorSets(
	const VulkanDevice &dev,
	const std::vector<VulkanDescriptorSet> &sets) {
	for (auto &s : sets) {
		if (dev.vk.vkFreeDescriptorSets(dev.handle, s.poolHandle, 1, &s.handle) != VK_SUCCESS) {
			throw DevaException("Could not free descriptor sets");
		}
	}
}