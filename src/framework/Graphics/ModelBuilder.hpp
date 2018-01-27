#ifndef DEVA_FRAMEWORK_GRAPHICS_MODEL_BUILDER_HPP
#define DEVA_FRAMEWORK_GRAPHICS_MODEL_BUILDER_HPP

#include "Config.hpp"

#include "Model.hpp"

namespace DevaFramework {

	typedef std::tuple<uint32_t, uint32_t, uint32_t> FaceIndexTriplet;

	class BasicModelBuilder {
	public:

		DEVA_FRAMEWORK_API BasicModelBuilder& addVertex(const vec4 &vertex);
		DEVA_FRAMEWORK_API BasicModelBuilder& addFace(const FaceIndexTriplet &face);

		DEVA_FRAMEWORK_API Mesh build() const;

	protected:
		std::vector<uint32_t> faces;
		std::vector<vec4> vertices;
	};

	class TexturedModelBuilder {
	public:

		DEVA_FRAMEWORK_API TexturedModelBuilder& addVertex(const vec4 &vertex, const vec3 &texCoords);
		DEVA_FRAMEWORK_API TexturedModelBuilder& addFace(const FaceIndexTriplet &face);

		DEVA_FRAMEWORK_API Mesh build();

	private:
		PackedVector<float, float, float, float, float, float, float> vertexTexCoords;
		std::vector<uint32_t> faces;
	};

}

#endif // DEVA_FRAMEWORK_GRAPHICS_MODEL_BUILDER_HPP