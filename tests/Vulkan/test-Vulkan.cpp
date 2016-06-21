#include <DevaEngine/DevaEngineInstance.hpp>

using namespace DevaEngine;

int main()
{
	DevaEngineInstanceCreateInfo info;
	info.window_height = 600;
	info.window_width = 800;
	info.window_name = "TEST!";

	DevaEngineInstance& engine = DevaEngineInstance::createInstance(info);
}