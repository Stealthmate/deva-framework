#ifndef DEVA_ENGINE_DEVA_ENGINE_INSTANCE_HPP
#define DEVA_ENGINE_DEVA_ENGINE_INSTANCE_HPP

#include "Config.hpp"

#include "Graphics\Vulkan\VulkanRenderer.hpp"
#include "Input/InputListener.hpp"

#include <DevaFramework\Include\Core.hpp>
#include <DevaFramework\Graphics\Vulkan.hpp>

#include <memory>
#include "Preferences.hpp"
namespace DevaEngine
{
	class Renderer;

	struct DevaEngineInstanceCreateInfo
	{
		uint32_t window_width;
		uint32_t window_height;
		std::string window_name;
		Preferences prefs;

		DEVA_ENGINE_API DevaEngineInstanceCreateInfo();
	};

	class DevaEngineInstance
	{
		uint64_t mID;
		std::shared_ptr<DevaFramework::Window> wnd;
		std::shared_ptr<InputListener> inputlstnr;

	public:
		DEVA_ENGINE_API static std::shared_ptr<DevaEngineInstance> createInstance(const DevaEngineInstanceCreateInfo &info);
	private:

		std::unique_ptr<Renderer> renderer;
		DevaEngineInstance(const DevaEngineInstanceCreateInfo &info, uint64_t id);
		DevaEngineInstance(const DevaEngineInstance &instance) = delete;
		DevaEngineInstance& operator=(const DevaEngineInstance &instance) = delete;
		DevaEngineInstance& operator=(DevaEngineInstance &&instance) = delete;
		

	public:

		DEVA_ENGINE_API DevaEngineInstance();

		DEVA_ENGINE_API DevaEngineInstance(DevaEngineInstance &&instance);
		DEVA_ENGINE_API ~DevaEngineInstance();

		DEVA_ENGINE_API Renderer& getRenderer();
		DEVA_ENGINE_API InputListener& getInputListener();

		DEVA_ENGINE_API bool update();

		DEVA_ENGINE_API void destroy();
	};

}

#endif //DEVA_ENGINE_DEVA_ENGINE_INSTANCE_HPP