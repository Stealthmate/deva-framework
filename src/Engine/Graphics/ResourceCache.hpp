#ifndef DEVA_ENGINE_GRAPHICS_RESOURCE_CACHE_HPP
#define DEVA_ENGINE_GRAPHICS_RESOURCE_CACHE_HPP

#include "Config.hpp"

namespace DevaFramework {
	class Mesh;
	class Image;
}

namespace DevaEngine {
	class ResourceCache {
	public:

		DevaFramework::Uuid addMesh(std::shared_ptr<DevaFramework::Mesh> &mesh);
		DevaFramework::Uuid addTexture(std::shared_ptr<DevaFramework::Image> &texture);

		std::shared_ptr<DevaFramework::Mesh> getMesh(DevaFramework::Uuid id);
		std::shared_ptr<DevaFramework::Image> getTexture(DevaFramework::Uuid id);

	private:

		std::unordered_map<DevaFramework::Uuid, std::shared_ptr<DevaFramework::Mesh>> meshes;
		std::unordered_map<DevaFramework::Uuid, std::shared_ptr<DevaFramework::Image>> textures;
	};
}

#endif //DEVA_ENGINE_GRAPHICS_RESOURCE_CACHE_HPP