#include <DevaEngine/DevaEngineInstance.hpp>
#include <DevaFramework\Graphics\Vulkan\Config.hpp>
#include <DevaFramework\Graphics\Vulkan\VulkanDeleter.hpp>

using namespace DevaEngine;
using namespace DevaFramework;
bool asd()
{
	std::exit(1);
	return true;
}

bool troll()
{
	DevaLogger::log << "TROLOLOLOL!\n";
	return true;
}

int main()
{

	DevaEngineInstanceCreateInfo info;
	info.window_height = 600;
	info.window_width = 800;
	info.window_name = "TEST!";

	DevaEngineInstance& engine = DevaEngineInstance::createInstance(info);
	DevaLogger::log.println("ALL IS GOOD!");
	//engine.getInputListener().bindKey(DevaFramework::Key::KEY_ESCAPE, asd);
	//engine.getInputListener().bindKey(DevaFramework::Key::KEY_0, troll);


	while (engine.update());
}