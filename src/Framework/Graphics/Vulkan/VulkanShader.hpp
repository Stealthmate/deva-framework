#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_SHADER_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_SHADER_HPP

#include "Config.hpp"
#include "VulkanDeleter.hpp"
#include "../../Util/ByteBuffer.hpp"


namespace DevaFramework {

	class VulkanShaderBuilder {

	public:
		DEVA_FRAMEWORK_API static VulkanShaderBuilder fromFile(const char *filepath);

	private:
		VulkanShaderBuilder(const ByteBuffer &bytecode);
		
	public:

		DEVA_FRAMEWORK_API VkPipelineShaderStageCreateInfo build();

		//TODO:
		DEVA_FRAMEWORK_API VulkanShaderBuilder& setVariable();


	};


}

#endif //DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_SHADER_HPP