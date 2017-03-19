#ifndef DEVA_ENGINE_GRAPHCIS_SCENE_BUILDER_HPP
#define DEVA_ENGINE_GRAPHCIS_SCENE_BUILDER_HPP

#include "Config.hpp"

#include "Scene.hpp"

namespace DevaEngine {

	class SceneBuilder {
	public:

		DEVA_ENGINE_API SceneBuilder& addObject(const Scene::ObjectID& id, std::unique_ptr<DevaFramework::Model> object);

		DEVA_ENGINE_API Scene build();

	private:
		std::unordered_map<Scene::ObjectID, std::unique_ptr<DevaFramework::Model>> objects;

	};

}

#endif // DEVA_ENGINE_GRAPHCIS_SCENE_BUILDER_HPP