#include <DevaEngine/DevaEngineInstance.hpp>

using namespace DevaEngine;

bool asd()
{
	std::exit(1);
	return true;
}

int main()
{
	DevaEngineInstanceCreateInfo info;
	info.window_height = 600;
	info.window_width = 800;
	info.window_name = "TEST!";

	DevaEngineInstance& engine = DevaEngineInstance::createInstance(info);
	engine.getInputListener().bindKey(DevaFramework::Key::KEY_ESCAPE, asd);

	while (engine.update());
}