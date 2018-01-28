#ifndef DEVA_ENGINE_GRAPHCIS_SCENE_BUILDER_HPP
#define DEVA_ENGINE_GRAPHCIS_SCENE_BUILDER_HPP

#include "Config.hpp"

namespace DevaFramework {
	struct Mesh;
}

namespace DevaEngine {

	class Scene;
	class SceneObject;

	class SceneBuilder {
	public:

		DEVA_ENGINE_API SceneBuilder& addObject(std::shared_ptr<SceneObject> obj, std::unique_ptr<DevaFramework::Mesh> object);

		DEVA_ENGINE_API Scene build();

	private:
		std::unordered_map<std::shared_ptr<SceneObject>, std::unique_ptr<DevaFramework::Mesh>> objects;

	};

}

#endif // DEVA_ENGINE_GRAPHCIS_SCENE_BUILDER_HPP