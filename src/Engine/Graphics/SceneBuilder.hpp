#ifndef DEVA_ENGINE_GRAPHCIS_SCENE_BUILDER_HPP
#define DEVA_ENGINE_GRAPHCIS_SCENE_BUILDER_HPP

#include "Config.hpp"

#include "Scene.hpp"

namespace DevaFramework {
	class Mesh;
}

namespace DevaEngine {

	class SceneBuilder {
	public:

		DEVA_ENGINE_API SceneBuilder& addObject(const SceneObjectID& id, std::unique_ptr<DevaFramework::Mesh> object);

		DEVA_ENGINE_API Scene build();

	private:
		std::unordered_map<SceneObjectID, std::unique_ptr<DevaFramework::Mesh>> objects;

	};

}

#endif // DEVA_ENGINE_GRAPHCIS_SCENE_BUILDER_HPP