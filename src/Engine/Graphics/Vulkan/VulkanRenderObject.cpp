#include "VulkanRenderObject.hpp"

using namespace DevaEngine;
using namespace DevaFramework;

DevaFramework::Vulkan::VulkanBufferID DevaEngine::VulkanRenderObject::buffer() const { return mBufferVertexIndex; }

VkDeviceSize DevaEngine::VulkanRenderObject::offsetIndex() const { return mOffsetIndex; }

uint32_t DevaEngine::VulkanRenderObject::indexCount() const { return mIndexCount; }

DevaFramework::Vulkan::VulkanBufferID DevaEngine::VulkanRenderObject::bufferMVP() const
{
	return mBufferMVP;
}

VkDeviceSize DevaEngine::VulkanRenderObject::offsetMVP() const
{
	return mOffsetMVP;
}

DevaEngine::VulkanRenderObject::VulkanRenderObject(
	const DevaFramework::Vulkan::VulkanBufferID & buffer,
	VkDeviceSize offsetIndex,
	uint32_t indexCount,
	VkDeviceSize offsetMVP,
	VkDescriptorSet dset)
	: mBufferVertexIndex(buffer),
	mOffsetIndex(offsetIndex),
	mIndexCount(indexCount), mBufferMVP(buffer), mOffsetMVP(offsetMVP), dset(dset) {}

	VkDescriptorSet VulkanRenderObject::getDescriptorSet() const {
	return dset;
}