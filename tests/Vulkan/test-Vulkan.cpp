#include <DevaEngine\DevaEngineInstance.hpp>
#include <DevaFramework\Graphics\Vulkan\Config.hpp>
#include <DevaFramework\Graphics\Vulkan\VulkanHandle.hpp>
#include <DevaFramework\Math\Vector.hpp>
#include <DevaFramework\Graphics\Mesh.hpp>
#include <DevaFramework\Graphics\MeshBuilder.hpp>
#include <DevaFramework\Math\MatrixFactory.hpp>
#include <DevaFramework\Math\Common.hpp>
#include <DevaFramework\Core\Uuid.hpp>

#include <DevaEngine\Graphics\Scene.hpp>
#include <DevaEngine\Graphics\SceneObject.hpp>
#include <DevaEngine\Graphics\Renderer.hpp>

#include <DevaEngine\Preferences.hpp>

using namespace DevaEngine;
using namespace DevaFramework;
using DevaFramework::Vulkan::LOG_VULKAN;

const int WIDTH = 800;
const int HEIGHT = 600;

template<typename T>
T& operator<<(T& lhs, const mat4 &rhs) {
	lhs << strf(rhs);
	return lhs;
}

vec4 normalize(vec4 v) {
	vec4 result;
	result[0] = v[0] / v[3];
	result[1] = v[1] / v[3];
	result[2] = v[2] / v[3];
	result[3] = v[3] / v[3];

	return result;
}

std::shared_ptr<Mesh> loadMesh(std::string filename) {
	std::istringstream ostr(readTextFile(filename.c_str()));
	TexturedModelBuilder bmb;
	size_t n = 0;
	ostr >> n;
	for (int i = 0;i < n;i++) {
		vec4 v1;
		vec3 v2;
		ostr >> v1[0] >> v1[1] >> v1[2] >> v1[3] >> v2[0] >> v2[1] >> v2[2];
		bmb.addVertex(v1, v2);
	}
	ostr >> n;
	for (int i = 0;i < n;i++) {
		uint32_t a, b, c;
		ostr >> a >> b >> c;
		bmb.addFace({ a, b, c });
	}

	return std::make_shared<Mesh>(bmb.build());
}

int main()
{
	DevaEngineInstanceCreateInfo info;
	info.window_height = 600;
	info.window_width = 800;
	info.window_name = "Vulkan Test";
	std::vector<std::string> layers;
	layers.push_back("VK_LAYER_LUNARG_standard_validation");
	layers.push_back("VK_LAYER_LUNARG_parameter_validation");
	layers.push_back("VK_LAYER_LUNARG_object_tracker");
	layers.push_back("VK_LAYER_LUNARG_core_validation");
	info.prefs.setPreference("vklayers", layers);
	std::vector<std::string> extensions;
	extensions.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
	extensions.push_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
	extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
	info.prefs.setPreference("vkextensions", extensions);

	LOG_VULKAN.setPrio(DevaLogger::LogLevel::ERR);
	LOG.setPrio(DevaLogger::LogLevel::UNSPECIFIED);

	std::shared_ptr<Model> models [] = { 
		std::make_shared<Model>(loadMesh("./resources/mesh3.txt"), nullptr, vec4()),
		std::make_shared<Model>(loadMesh("./resources/mesh.txt"), nullptr, vec4()) 
	};
	
	mat4 mvp;
	//mvp = mvp * Math::projection(M_PI / 3, 4.0 / 3.0, 0.1f, 100.f);
	//mvp = mvp * Math::translate({ 0.f, 0.f, 0.f });
	mvp = mvp * Math::rotateZ(M_PI / 2.0);

	try {
		auto scobj = std::make_shared<SceneObject>(models[0]);

		std::shared_ptr<Scene> scene = std::make_shared<Scene>();

		auto engine = DevaEngineInstance::createInstance(info);
		LOG.i("SUCCESS!");
		auto &renderer = engine->getRenderer();

		scobj->update().setMVP(mvp).commit();
		scene->update().addObjects({ scobj }).commit();

		renderer.prepareScene(scene);

		int deg = 0;
		int dm = 3;
		float c = 0;
		float dc = 0.001f;
		int i = 0;
		
		while (engine->update()) {
			if (c + dc > 2) {
				c = 0;
				scobj->update().setModel(models[1 - i]).commit();
				i = 1 - i;
				//if (scene->getAllObjectIDs().size() == 1) id1 = scene->addObject(std::move(scobj));
				//else scobj = scene->removeObject(id1);
			}
			c += dc;
			//mvp = mvp * Math::rotateZ(M_PI * c);
			scobj->update().setMVP(mvp).commit();
		}
		LOG.i("Over");

		engine->destroy();
	}
	catch (std::exception &ex) {
		std::cout << ex.what() << std::endl;
	}
}