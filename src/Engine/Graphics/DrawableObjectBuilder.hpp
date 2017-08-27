#ifndef DEVA_ENGINE_GRAPHICS_DRAWABLE_OBJECT_BUILDER_HPP
#define DEVA_ENGINE_GRAPHICS_DRAWABLE_OBJECT_BUILDER_HPP

#include "Config.hpp"
#include <DevaFramework\Util\MultiTypeVector.hpp">

#include "DrawableObject.hpp"

namespace DevaEngine {
	
	class DrawableObjectBuilder {
	public:
		DEVA_ENGINE_API virtual DrawableObject build() = 0;
	};

	class BasicDrawableObjectBuilder {

		DevaFramework::TypedPackedVector<DevaFramework::vec4> vertices;
		DevaFramework::TypedPackedVector<DevaFramework::ivec3> faceIndices;

	};

}

#endif //DEVA_ENGINE_GRAPHICS_DRAWABLE_OBJECT_BUILDER_HPP