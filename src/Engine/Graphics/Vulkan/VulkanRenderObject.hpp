#ifndef DEVA_ENGINE_GRAPHICS_VULKAN_VULKAN_RENDER_OBJECT_HPP
#define DEVA_ENGINE_GRAPHICS_VULKAN_VULKAN_RENDER_OBJECT_HPP

#include "Config.hpp"
#include "../GraphicsObject.hpp"

namespace DevaEngine {

	class VulkanRenderObject {
	public:

		DEVA_ENGINE_API static VulkanRenderObject load(const GraphicsObject &model, const DevaFramework::VulkanDevice &dev);

	private:
		DevaFramework::VulkanBuffer buffer;

	};

}


#endif // DEVA_ENGINE_GRAPHICS_VULKAN_VULKAN_RENDER_OBJECT_HPP