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
	const std::vector<byte_t> &vertexData,
	size_t vertexCount,
	const std::vector<VertexDataElementDescription> &vertexElementDescriptions,
	const std::vector<uint32_t> &faceIndices) 
	: mVertexData(vertexData), 
	mVertexCount(vertexCount), 
	mVertexElementDescriptions(vertexElementDescriptions),
	mFaceIndices(faceIndices) {}

size_t Model::vertexSize() const 
{
	return sumComponentSizes(mVertexElementDescriptions);
}