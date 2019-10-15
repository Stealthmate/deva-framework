#ifndef DEVA_FRAMEWORK_GRAPHICS_MESH_HPP
#define DEVA_FRAMEWORK_GRAPHICS_MESH_HPP

#include "Config.hpp"

#include "..\Include\Math.hpp"

#include <vector>

namespace DevaFramework
{
	enum VertexComponentType {
		INT,
		UINT,
		FLOAT,
		UFLOAT,
		NORM,
		UNORM
	};

	struct VertexDataElementDescription {
		size_t size;
		VertexComponentType type;
		std::vector<size_t> componentBitsizes;
	};

	struct Mesh {

		//Vertex size and face data is calculated autmatically
		DEVA_FRAMEWORK_API Mesh(
			const std::vector<byte_t> &vertexData,
			size_t vertexCount,
			const std::vector<VertexDataElementDescription> &vertexElementDescriptions);

		const std::vector<byte_t> vertexData;
		const size_t vertexCount;
		const std::vector<VertexDataElementDescription> vertexElementDescriptions;
		const size_t vertexSize;
		const size_t faceDataOffset;
		const size_t faceCount;
	};
}

#endif //DEVA_FRAMEWORK_GRAPHICS_MODEL_HPP