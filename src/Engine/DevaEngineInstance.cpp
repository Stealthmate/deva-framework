#include "DevaEngineInstance.hpp"

#include <vector>

using namespace DevaEngine;
using namespace DevaFramework;

namespace
{
	std::vector<DevaEngineInstance> instances(0);

	class impl_WindowListener : public WindowEventListener
	{
	public:

		virtual bool onKeyDown(Key k)
		{
			DevaLogger::log << "Ya!\n";
			return true;
		}
		virtual bool onKeyUp(Key k)
		{
			return true;
		}

	};

}

DevaEngineInstanceCreateInfo::DevaEngineInstanceCreateInfo()
{
	window_width = 0;
	window_height = 0;
	window_name = "";
}


DevaEngineInstance& DevaEngineInstance::createInstance(const DevaEngineInstanceCreateInfo &info)
{
	instances.push_back(DevaEngineInstance(info));
	return instances[instances.size() - 1];
}

DevaEngineInstance::DevaEngineInstance()
	: wnd(nullptr), renderer(), inputlstnr(new InputListener())
{

}

DevaEngineInstance::DevaEngineInstance(const DevaEngineInstanceCreateInfo &info)
	:wnd(std::move(Window::openWindow(info.window_width, info.window_height, info.window_name))), renderer(), inputlstnr(new InputListener())
{
	wnd->getEventObserver().attachListener(
		std::static_pointer_cast<WindowEventListener, impl_WindowListener>(
			std::shared_ptr<impl_WindowListener>(new impl_WindowListener())));
}

DevaEngineInstance::DevaEngineInstance(DevaEngineInstance &&instance)
	: wnd(std::move(instance.wnd)), renderer(std::move(instance.renderer)), inputlstnr(std::move(instance.inputlstnr))
{
	wnd->setUserData(static_cast<void*>(this));
}

bool DevaEngineInstance::update()
{
	return wnd->update();
}

Renderer& DevaEngineInstance::getRenderer()
{
	return renderer;
}

InputListener& DevaEngineInstance::getInputListener()
{
	return *inputlstnr;
}