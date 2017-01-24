#include "Common.hpp"
#include "VulkanException.hpp"

#include "../../Util/Common.hpp"

using namespace DevaFramework;

VulkanDeleter<VkShaderModule> DevaFramework::vulkanShaderFromFile(const VulkanDevice &dev, const char *filepath)
{
	auto src = readBinaryFile(filepath);

	VkShaderModuleCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = src.size();
	createInfo.pCode = (uint32_t*)src.buf().data();

	auto& vk = dev.getFunctionSet();

	VulkanDeleter<VkShaderModule> shaderModule{dev.getHandle(), vk.vkDestroyShaderModule};

	if (vk.vkCreateShaderModule(dev.getHandle(), &createInfo, nullptr, shaderModule.replace()) != VK_SUCCESS) {
		throw DevaException("failed to create shader module!");
	}

	return shaderModule;
}