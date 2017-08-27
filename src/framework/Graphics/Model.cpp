#include "Model.hpp"

using namespace DevaFramework;

namespace {
	size_t sumComponentSizes(const std::vector<VertexDataElementDescription> &elements)
	{
		size_t sum = 0;
		for (auto & c : elements)
		{
			sum += c.size;
		}

		return sum;
	}
}

Model::Model(
	std::vector<byte_t> vertexData,
	size_t vertexCount,
	const std::vector<VertexDataElementDescription> &vertexElementDescriptions,
	const std::vector<uint32_t> &faceIndices) 
	: mVertexData(std::move(vertexData)), 
	mVertexCount(vertexCount), 
	mVertexElementDescriptions(vertexElementDescriptions),
	mFaceIndices(faceIndices) {}

Model::Model(
	ByteBuffer vertexData,
	size_t vertexCount,
	const std::vector<VertexDataElementDescription> &vertexElementDescriptions,
	const std::vector<uint32_t> &faceIndices)
	: mVertexData(std::move(vertexData.release())),
	mVertexCount(vertexCount),
	mVertexElementDescriptions(vertexElementDescriptions),
	mFaceIndices(faceIndices) {}

size_t Model::vertexSize() const 
{
	return sumComponentSizes(mVertexElementDescriptions);
}

ByteBuffer Model::onRelease() {
	return std::move(mVertexData.release());
}