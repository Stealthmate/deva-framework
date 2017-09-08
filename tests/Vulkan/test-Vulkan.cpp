#include <DevaEngine\DevaEngineInstance.hpp>
#include <DevaFramework\Graphics\Vulkan\Config.hpp>
#include <DevaFramework\Graphics\Vulkan\VulkanHandle.hpp>
#include <DevaFramework\Math\Vector.hpp>
#include <DevaFramework\Graphics\ModelBuilder.hpp>

using namespace DevaEngine;
using namespace DevaFramework;

const int WIDTH = 800;
const int HEIGHT = 600;

int main()
{
	//try {

		DevaEngineInstanceCreateInfo info;
		info.window_height = 600;
		info.window_width = 800;
		info.window_name = "Vulkan Test";

		LOG_VULKAN.setPrio(DevaLogger::LogLevel::DEBUG);
		LOG.setPrio(DevaLogger::LogLevel::DEBUG);

		TexturedModelBuilder bmb;
		auto model = std::make_shared<DrawableObject>(std::move(bmb
			.addVertex({ -0.5f, 0.f, 0.f, 1.f }, { 0.0f, .5f, .8f })
			.addVertex({ 0.f, 1.f, 0.f, 1.f }, { 0.0f, .3f, .7f })
			.addVertex({ 0.5f, 0.f, 0.f, 1.f }, { 0.0f, .7f, .3f })
			.addFace({ 0, 2, 1 })
			.build()));
		
		std::shared_ptr<Scene> scene = std::make_shared<Scene>();
		Uuid id = scene->addObject(model);
		Uuid id1;
		auto &mobj = scene->getObject(id);

		auto engine = DevaEngineInstance::createInstance(info);
		LOG.i("SUCCESS!");
		auto &renderer = engine->getRenderer();
		renderer.render(scene);
		
		bmb = TexturedModelBuilder();
		model = std::make_shared<DrawableObject>(bmb
			.addVertex({ -0.5f, 0.f, 0.f, 1.f }, { 1.0f, .5f, .8f })
			.addVertex({ 0.f, -1.f, 0.f, 1.f }, { 1.0f, .3f, .7f })
			.addVertex({ 0.5f, 0.f, 0.f, 1.f }, { 1.0f, .7f, .3f })
			.addFace({ 0, 1, 2 })
			.build());

		size_t c = 0;
		while (engine->update()) {
			c++;
			if (c > 1000) {
				c = 0;
				//if (scene->getAllObjectIDs().size() == 1) id1 = scene->addObject(std::move(model));
				//else model = scene->removeObject(id1);
			}
		}
		LOG.i("Over");

		engine->destroy();

	/*}
	catch (std::exception ex) {
		std::cout << "WTF\n";
		std::cout << ex.what() << std::endl;
	}*/
}