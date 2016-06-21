#include "DevaEngineInstance.hpp"

#include <vector>

using namespace DevaEngine;
using namespace DevaFramework;

namespace
{
	std::vector<DevaEngineInstance> instances(0);

	class KeyboadInputListener : public WindowEventListener
	{
		bool onKeyEvent(Window &wnd, WindowEventStruct_KeyEvent evtinfo)
		{
			//if(wnd != this->wnd)
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
	: wnd(nullptr), renderer()
{

}

DevaEngineInstance::DevaEngineInstance(const DevaEngineInstanceCreateInfo &info)
	:wnd(&Window::openWindow(info.window_width, info.window_height, info.window_name))
{

}

DevaEngineInstance::DevaEngineInstance(DevaEngineInstance &&instance)
	: wnd(std::move(instance.wnd)), renderer(std::move(instance.renderer))
{}


Renderer& DevaEngineInstance::getRenderer()
{
	return renderer;
}