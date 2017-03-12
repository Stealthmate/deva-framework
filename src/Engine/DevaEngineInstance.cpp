#include "DevaEngineInstance.hpp"

#include <vector>

using namespace DevaEngine;
using namespace DevaFramework;

namespace
{
	std::unordered_map<uint64_t, std::shared_ptr<DevaEngineInstance>> instances(0);

	class impl_WindowListener : public WindowEventListener
	{
	public:

		virtual bool onKeyDown(Key k)
		{
			LOG.i("Ya!\n");
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


std::shared_ptr<DevaEngineInstance> DevaEngineInstance::createInstance(const DevaEngineInstanceCreateInfo &info)
{
	size_t id = instances.size();
	instances.insert({ id, std::shared_ptr<DevaEngineInstance>(new DevaEngineInstance(info, id)) });
	return instances[id];
}

DevaEngineInstance::DevaEngineInstance()
	: wnd(nullptr), renderer(), inputlstnr(new InputListener()), mID(UINT64_MAX) {}

DevaEngineInstance::DevaEngineInstance(const DevaEngineInstanceCreateInfo &info, uint64_t id)
	: wnd(std::move(Window::openWindow(info.window_width, info.window_height, info.window_name))), inputlstnr(new InputListener()), mID(id)
{
	renderer = std::make_unique<VulkanRenderer>(*wnd);
	wnd->getEventObserver().attachListener(
		std::static_pointer_cast<WindowEventListener, impl_WindowListener>(
			std::shared_ptr<impl_WindowListener>(new impl_WindowListener())));
}

DevaEngineInstance::DevaEngineInstance(DevaEngineInstance &&instance)
	: wnd(std::move(instance.wnd)), renderer(std::move(instance.renderer)), inputlstnr(std::move(instance.inputlstnr)), mID(instance.mID)
{
	wnd->setUserData(static_cast<void*>(this));
	instance.mID = UINT64_MAX;
}

bool DevaEngineInstance::update()
{
	renderer->renderExample();
	return wnd->update();
}

Renderer& DevaEngineInstance::getRenderer()
{
	return *renderer;
}

InputListener& DevaEngineInstance::getInputListener()
{
	return *inputlstnr;
}

void DevaEngineInstance::destroy() {
	auto i = instances.find(mID);
	if (i != instances.end()) {
		instances.erase(i);
	}
}

DevaEngineInstance::~DevaEngineInstance() {
	destroy();
}