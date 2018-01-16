#include "VulkanRenderObject.hpp"

using namespace DevaEngine;
using namespace DevaFramework;

DevaFramework::Vulkan::VulkanBufferID DevaEngine::VulkanRenderObject::buffer() const { return mBufferVertexIndex; }

uint32_t DevaEngine::VulkanRenderObject::indexCount() const { return mIndexCount; }

VulkanRenderObject::Offsets DevaEngine::VulkanRenderObject::offsets() const
{
	return mOffsets;
}

DevaEngine::VulkanRenderObject::VulkanRenderObject(
	const DevaFramework::Vulkan::VulkanBufferID & buffer,
	uint32_t indexCount,
	Offsets offsets,
	VkDescriptorSet dset)
	: mBufferVertexIndex(buffer),
	mIndexCount(indexCount), mOffsets(offsets), mDescriptorSet(dset) {}

	VkDescriptorSet VulkanRenderObject::getDescriptorSet() const {
	return mDescriptorSet;
}