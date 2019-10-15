#include "VulkanVertexInputBinding.hpp"

using namespace DevaFramework;
using namespace DevaFramework::Vulkan;

void VertexInputBinding::addAttribute(const VkVertexInputAttributeDescription &attr)
{
	if (attr.binding != mBinding) LOG_VULKAN.w("Attribute binding " + strf(attr.binding) + " does not match parent " + strf(mBinding));
	VkVertexInputAttributeDescription a = attr;
	a.binding = mBinding;
	mAttributes.push_back(a);
}