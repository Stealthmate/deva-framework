#ifndef DEVA_ENGINE_VULKAN_RENDERER_HPP
#define DEVA_ENGINE_VULKAN_RENDERER_HPP

#include "Config.hpp"

#include "Renderer.hpp"
#include <DevaFramework\Graphics/Vulkan/VulkanInstance.hpp>

namespace DevaEngine
{
	class VulkanRenderer : public Renderer
	{

		//VulkanSurface surface;

	public:

		VulkanRenderer() {}

		virtual void renderExample() {}

	};
}


#endif //DEVA_ENGINE_VULKAN_RENDERER_HPP