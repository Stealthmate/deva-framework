#ifndef DEVA_ENGINE_VULKAN_RENDERER_HPP
#define DEVA_ENGINE_VULKAN_RENDERER_HPP

#include "Config.hpp"

#include "Renderer.hpp"
#include <DevaFramework\Graphics/Vulkan/VulkanInstance.hpp>
#include <DevaFramework\Graphics/Vulkan/VulkanDevice.hpp>

namespace DevaEngine
{
	class VulkanRenderer : public Renderer
	{

		DevaFramework::VulkanInstance instance;
		DevaFramework::VulkanDevice main_device;

	public:

		DEVA_ENGINE_API VulkanRenderer();

		DEVA_ENGINE_API virtual void renderExample();

	};
}


#endif //DEVA_ENGINE_VULKAN_RENDERER_HPP