#include<DevaFramework\Include\Core.hpp>
#include <DevaEngine\DevaEngineInstance.hpp>
#include <DevaFramework\Graphics\Vulkan\Config.hpp>
#include <DevaFramework\Graphics\Vulkan\VulkanHandle.hpp>
#include <DevaFramework\Math\Vector.hpp>
#include <DevaFramework\Graphics\ModelBuilder.hpp>

#include <DevaEngine\Graphics\Scene.hpp>
#include <DevaEngine\Graphics\Renderer.hpp>

using namespace DevaFramework;
using namespace DevaEngine;
using namespace std;
using DevaFramework::Vulkan::LOG_VULKAN;

void printpack(Pack<float, float, float, float, float, float, float> p) {
	LOG << std::get<0>(p) << " ";
	LOG << std::get<1>(p) << " ";
	LOG << std::get<2>(p) << " ";
	LOG << std::get<3>(p) << " ";
	LOG << std::get<4>(p) << " ";
	LOG << std::get<5>(p) << " ";
	LOG << std::get<6>(p) << " ";
	LOG << LOG.endl;
}

int main() {
	DevaEngineInstanceCreateInfo info;
	info.window_height = 600;
	info.window_width = 800;
	info.window_name = "Vulkan Test";

	LOG_VULKAN.setPrio(DevaLogger::LogLevel::DEBUG);
	//LOG.setPrio(DevaLogger::LogLevel::DEBUG);

	TexturedModelBuilder bmb;
	auto model = std::make_shared<DrawableObject>(bmb
		.addVertex({ -0.5f, 0.f, 0.f, 1.f }, { 0.0f, .5f, .8f })
		.addVertex({ 0.f, 1.f, 0.f, 1.f }, { 0.0f, .3f, .7f })
		.addVertex({ 0.5f, 0.f, 0.f, 1.f }, { 0.0f, .7f, .3f })
		.addFace({ 0, 2, 1 })
		.build());

	std::shared_ptr<Scene> scene = std::make_shared<Scene>();
	Uuid id = scene->addObject(model);

	auto engine = DevaEngineInstance::createInstance(info);
	auto &renderer = engine->getRenderer();
	renderer.prepareScene(scene);

	size_t c = 0;
	while (engine->update()) {
	}
	LOG.i("Over");

	engine->destroy();
}