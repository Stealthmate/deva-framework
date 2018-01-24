#define NOMINMAX
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


		bool onKeyDown(Key k) override
		{
			LOG.i("Ya!\n");
			return true;
		}
		virtual bool onKeyUp(Key k) override
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

constexpr int FRAMERATEMARK = 100;
std::array<long long, FRAMERATEMARK> framerate;
static int i = 0;
static double fps = 0;
static double AVG = 0;
static long long lastFrame = 0;
#include <DevaFramework\Util\Time.hpp>

void printframerate() {
	float avg = 0;
	float sum = 0;
	for (int j = 0;j < FRAMERATEMARK;j++) {
		sum += framerate[j] / 1000000.f;
		//LOG.d("FRAME " + strm(framerate[j]));
	}
	avg = sum / (float)FRAMERATEMARK;
	LOG.d("Framerate: " + strm(1.f / avg));
}

bool DevaEngineInstance::update()
{
	auto t1 = getSystemTime(TimeUnit::MICROSECONDS);
	//if (t1 - lastFrame < 12000) return wnd->update();
	renderer->renderExample();
	bool result = wnd->update();
	auto t2 = getSystemTime(TimeUnit::MICROSECONDS);
	if (lastFrame == 0) t2 = t2 - t1;
	auto sec = (t2 - lastFrame) / 1000000.0;
	lastFrame = t2;
	AVG = AVG + sec;
	i++;
	fps = i / AVG;
	if (i == FRAMERATEMARK) {
		LOG.d("SEC " + strm(AVG / i));
		LOG.d("FPS: " + strm(fps));
		AVG = 0;
		i = 0;
	}
	return result;
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
	auto &i = instances.find(mID);
	if (i != instances.end()) {
		instances.erase(i);
	}
}

DevaEngineInstance::~DevaEngineInstance() {
	destroy();
}