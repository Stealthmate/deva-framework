#include "VertexInputBinding.hpp"

using namespace DevaFramework;
using namespace DevaFramework::Vulkan;

void VertexInputBinding::addAttribute(const VkVertexInputAttributeDescription &attr)
{
	if (attr.binding != mBinding) VULKAN_WARN.println("Attribute binding " + strm(attr.binding) + " does not match parent " + strm(mBinding));
	VkVertexInputAttributeDescription a = attr;
	a.binding = mBinding;
	mAttributes.push_back(a);
}