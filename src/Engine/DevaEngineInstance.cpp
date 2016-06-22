#include "DevaEngineInstance.hpp"

#include <vector>

using namespace DevaEngine;
using namespace DevaFramework;

namespace
{
	std::vector<DevaEngineInstance> instances(0);

	class _impl_KeyboardListener : public WindowEventListener
	{
		bool alt = false;
		bool ctrl = false;
		bool super = false;

	public:
		virtual bool onKeyEvent(WindowEventStruct_KeyEvent evtinfo)
		{
			uint8_t mods = 0;
			if (alt) mods += MOD_ALT;
			if (ctrl) mods += MOD_CTRL;
			if (super) mods += MOD_SUPER;

			KeyboardAction act;

			DevaEngineInstance *instance = static_cast<DevaEngineInstance*>(evtinfo.wnd->getUserData());

			switch (evtinfo.evt)
			{
			case WindowEvent::EVENT_KEY_DOWN:
			{
				if (evtinfo.wasPressed)
					instance->getInputListener().onKeyboardAction(evtinfo.key, KeyboardAction::KEY_REPEAT, mods);
				else instance->getInputListener().onKeyboardAction(evtinfo.key, KeyboardAction::KEY_PRESS, mods);
			}
			case WindowEvent::EVENT_KEY_UP:
			{
				instance->getInputListener().onKeyboardAction(evtinfo.key, KeyboardAction::KEY_RELEASE, mods);
			}
			}

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
	:wnd(&Window::openWindow(info.window_width, info.window_height, info.window_name)), renderer(), inputlstnr(new InputListener())
{
	wnd->getEventObserver().attachListener(WindowEvent::EVENT_KEY_DOWN, 
		std::static_pointer_cast<WindowEventListener, _impl_KeyboardListener>(
			std::shared_ptr<_impl_KeyboardListener>(new _impl_KeyboardListener())));
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