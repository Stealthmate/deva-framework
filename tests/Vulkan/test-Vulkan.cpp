#include <DevaEngine\DevaEngineInstance.hpp>
#include <DevaFramework\Graphics\Vulkan\Config.hpp>
#include <DevaFramework\Graphics\Vulkan\VulkanHandle.hpp>

using namespace DevaEngine;
using namespace DevaFramework;

const int WIDTH = 800;
const int HEIGHT = 600;

int main()
{
	DevaEngineInstanceCreateInfo info;
	info.window_height = 600;
	info.window_width = 800;
	info.window_name = "Vulkan Test";

	LOG_VULKAN.setPrio(DevaLogger::LogLevel::DEBUG);
	LOG.setPrio(DevaLogger::LogLevel::DEBUG);

	auto engine = DevaEngineInstance::createInstance(info);
	LOG.i("SUCCESS!");

	while (engine->update());
	LOG.i("Over");

	engine->destroy();
}