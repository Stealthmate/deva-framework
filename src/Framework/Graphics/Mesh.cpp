#include "Mesh.hpp"

using namespace DevaFramework;

namespace {
	size_t calculateVertexSize(const std::vector<VertexDataElementDescription> &elements)
	{
		size_t sum = 0;
		for (auto & c : elements)
		{
			sum += c.size;
		}

		return sum;
	}
}

Mesh::Mesh(
	const std::vector<byte_t> &vertexData,
	size_t vertexCount,
	const std::vector<VertexDataElementDescription> &vertexDescriptions) 
	: vertexData(vertexData), 
	vertexCount(vertexCount), 
	vertexElementDescriptions(vertexDescriptions),
	vertexSize(calculateVertexSize(vertexDescriptions)),
	faceDataOffset(vertexSize * vertexCount),
	faceCount((vertexData.size() - faceDataOffset) / (sizeof(uint32_t) * 3)) {}

/*
Mesh::Mesh(
	std::vector<byte_t> vertexData,
	size_t vertexCount,
	const std::vector<VertexDataElementDescription> &vertexElementDescriptions,
	const std::vector<uint32_t> &faceIndices) 
	: mVertexData(std::move(vertexData)), 
	mVertexCount(vertexCount), 
	mVertexElementDescriptions(vertexElementDescriptions),
	mFaceIndices(faceIndices) {}


Mesh::Mesh(
	ByteBuffer vertexData,
	size_t vertexCount,
	const std::vector<VertexDataElementDescription> &vertexElementDescriptions,
	const std::vector<uint32_t> &faceIndices)
	: mVertexData(std::move(vertexData.release())),
	mVertexCount(vertexCount),
	mVertexElementDescriptions(vertexElementDescriptions),
	mFaceIndices(faceIndices) {}

size_t Mesh::vertexSize() const 
{
	return sumComponentSizes(mVertexElementDescriptions);
}
/*
ByteBuffer Mesh::onRelease() {
	return std::move(mVertexData.release());
}*/