#ifndef DEVA_ENGINE_GRAPHICS_GRAPHICS_OBJECT_HPP
#define DEVA_ENGINE_GRAPHICS_GRAPHICS_OBJECT_HPP

#include "Config.hpp"
#include <DevaFramework\Math\Geometry\Triangle.hpp>
#include <DevaFramework\Core\Identifiable.hpp>

namespace DevaEngine {
	class GraphicsObject : public DevaFramework::Identifiable<uint32_t> {
	public:

		DEVA_ENGINE_API GraphicsObject(const std::vector<DevaFramework::Triangle> &triangles) {}

	private:
		std::vector<DevaFramework::Triangle> triangles;
	};
}

#endif // DEVA_ENGINE_GRAPHICS_GRAPHICS_OBJECT_HPP