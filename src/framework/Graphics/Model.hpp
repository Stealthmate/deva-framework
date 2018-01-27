#ifndef DEVA_FRAMEWORK_GRAPHICS_MODEL_HPP
#define DEVA_FRAMEWORK_GRAPHICS_MODEL_HPP

#include "Config.hpp"

#include "..\Include\Math.hpp"
#include "..\Util\MultiTypeVector.hpp"

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

	struct Mesh1 {
		DEVA_FRAMEWORK_API Mesh1(
			const std::vector<byte_t> &vertexData,
			size_t vertexCount,
			const std::vector<VertexDataElementDescription> &vertexElementDescriptions);

		const std::vector<byte_t> vertexData;
		const size_t vertexCount;
		const std::vector<VertexDataElementDescription> vertexElementDescriptions;
		const size_t faceDataOffset;
		const size_t faceCount;
	};

	class Mesh {
	public:

		DEVA_FRAMEWORK_API Mesh(
			std::vector<byte_t> vertexData,
			size_t vertexCount,
			const std::vector<VertexDataElementDescription> &vertexElementDescriptions,
			const std::vector<uint32_t> &faceIndices);
		DEVA_FRAMEWORK_API Mesh(
			ByteBuffer vertexData,
			size_t vertexCount,
			const std::vector<VertexDataElementDescription> &vertexElementDescriptions,
			const std::vector<uint32_t> &faceIndices);

		DEVA_FRAMEWORK_API const std::vector<byte_t>& vertexData() const { return mVertexData.buf(); }
		DEVA_FRAMEWORK_API size_t vertexCount() const { return mVertexCount; }
		DEVA_FRAMEWORK_API const std::vector<VertexDataElementDescription>& elements() const { return mVertexElementDescriptions; }
		DEVA_FRAMEWORK_API size_t vertexSize() const;
		DEVA_FRAMEWORK_API const std::vector<uint32_t>& faceIndices() const { return mFaceIndices; }

	private:
		ByteBuffer mVertexData;
		size_t mVertexCount;
		std::vector<VertexDataElementDescription> mVertexElementDescriptions;

		std::vector<uint32_t> mFaceIndices;
	};

}

#endif //DEVA_FRAMEWORK_GRAPHICS_MODEL_HPP