#ifndef DEVA_FRAMEWORK_GRAPHICS_MESH_BUILDER_HPP
#define DEVA_FRAMEWORK_GRAPHICS_MESH_BUILDER_HPP

#include "Config.hpp"

#include "../Math/Vector.hpp"

namespace DevaFramework {

	struct Mesh;

	class BasicModelBuilder {
	public:

		DEVA_FRAMEWORK_API BasicModelBuilder& addVertex(const vec4 &vertex);
		DEVA_FRAMEWORK_API BasicModelBuilder& addFace(const uvec3 &face);

		DEVA_FRAMEWORK_API Mesh build() const;

	protected:
		std::vector<vec4> vertices;
		std::vector<uvec3> faces;
	};

	class TexturedModelBuilder {
	public:

		DEVA_FRAMEWORK_API TexturedModelBuilder& addVertex(const vec4 &vertex, const vec3 &texCoords);
		DEVA_FRAMEWORK_API TexturedModelBuilder& addFace(const uvec3 &face);

		DEVA_FRAMEWORK_API Mesh build();

	private:
		std::vector<vec4> vertices;
		std::vector<vec3> texCoords;
		std::vector<uvec3> faces;
	};

}

#endif // DEVA_FRAMEWORK_GRAPHICS_MODEL_BUILDER_HPP