#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_COMMON_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_COMMON_HPP

#include "Config.hpp"

#include "VulkanDeleter.hpp"

namespace DevaFramework {

	DEVA_FRAMEWORK_API VulkanDeleter<VkShaderModule> vulkanShaderFromFile(const VulkanDevice &dev, const char *filepath);

}

#endif //DEVA_FRAMEWORK_GRAPHICS_VULKAN_COMMON_HPP