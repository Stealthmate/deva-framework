#ifndef DEVA_ENGINE_GRAPHICS_MODEL_HPP
#define DEVA_ENGINE_GRAPHICS_MODEL_HPP

#include "Config.hpp"

#include <DevaFramework\Math\Vector.hpp>

namespace DevaFramework {
	class Mesh;
	class Image;
}

namespace DevaEngine {
	struct Model {

		Model(
			std::shared_ptr<DevaFramework::Mesh> mesh,
			std::shared_ptr<DevaFramework::Image> texture,
			const DevaFramework::vec4 &frontVector) : mesh(mesh), texture(texture), frontVector(frontVector) {}

		const std::shared_ptr<const DevaFramework::Mesh> mesh;
		const std::shared_ptr<const DevaFramework::Image> texture;
		const DevaFramework::vec4 frontVector;
	};
}

#endif //DEVA_ENGINE_GRAPHICS_MODEL_HPP