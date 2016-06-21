#ifndef DEVA_ENGINE_DEVA_ENGINE_INSTANCE_HPP
#define DEVA_ENGINE_DEVA_ENGINE_INSTANCE_HPP

#include "Config.hpp"

#include "Renderer.hpp"
#include "Input/InputListener.hpp"
#include <DevaFramework/Deva.hpp>

namespace DevaEngine
{

	struct DevaEngineInstanceCreateInfo
	{
		uint32_t window_width;
		uint32_t window_height;
		std::string window_name;

		DEVA_ENGINE_API DevaEngineInstanceCreateInfo();
	};

	class DevaEngineInstance
	{

		std::shared_ptr<DevaFramework::Window> wnd;
		std::shared_ptr<InputListener> inputlstnr;

	public:
		DEVA_ENGINE_API static DevaEngineInstance& createInstance(const DevaEngineInstanceCreateInfo &info);
	private:

		Renderer renderer;

		DevaEngineInstance(const DevaEngineInstanceCreateInfo &info);
		

	public:

		DEVA_ENGINE_API DevaEngineInstance();

		DEVA_ENGINE_API DevaEngineInstance(const DevaEngineInstance &instance) = delete;
		DEVA_ENGINE_API DevaEngineInstance(DevaEngineInstance &&instance);

		DEVA_ENGINE_API Renderer& getRenderer();

	};

}

#endif //DEVA_ENGINE_DEVA_ENGINE_INSTANCE_HPP