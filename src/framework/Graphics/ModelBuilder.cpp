#include "ModelBuilder.hpp"

using namespace DevaFramework;

template <typename T, std::size_t N1, std::size_t N2>
std::array<T, N1 + N2> concatenateArrays(std::array<T, N1> arr1, const std::array<T, N2> &arr2) {
	std::array<T, N1 + N2> concatarr;
	for (size_t i = 0;i < N1 + N2;i++) {
		concatarr[i] = i < N1 ? arr1[i] : arr2[i - N1];
	}

	return concatarr;
}

BasicModelBuilder& BasicModelBuilder::addVertex(const vec4 &vertex) 
{
	this->vertices.push_back(vertex);

	return *this;
}

BasicModelBuilder& BasicModelBuilder::addFace(const FaceIndexTriplet &face)
{
	this->faces.push_back(std::get<0>(face));
	this->faces.push_back(std::get<1>(face));
	this->faces.push_back(std::get<2>(face));

	return *this;
}

Model BasicModelBuilder::build() const
{
	std::vector<byte_t> vertexData;
	for (auto &v : vertices) {
		auto bytes = v.asBytes();
		for (auto b : bytes)
			vertexData.push_back(b);
	}

	VertexDataElementDescription eld;
	size_t bitsize = sizeof(float) * 8;
	eld.componentBitsizes = { bitsize, bitsize, bitsize, bitsize};
	eld.size = 4 * sizeof(float);
	eld.type = VertexComponentType::FLOAT;
	
	return Model(vertexData, vertices.size(), { eld }, faces);
}

TexturedModelBuilder& TexturedModelBuilder::addVertex(const vec4 &vertex, const vec3 &texCoords) {
	vertexTexCoords.push_back({ vertex[0], vertex[1], vertex[2], vertex[3], texCoords[0], texCoords[1], texCoords[2] });
	return *this;
}

TexturedModelBuilder&::TexturedModelBuilder::addFace(const FaceIndexTriplet &face) {
	faces.push_back(std::get<0>(face));
	faces.push_back(std::get<1>(face));
	faces.push_back(std::get<2>(face));

	return *this;
}

Model TexturedModelBuilder::build()
{
	VertexDataElementDescription eld;
	size_t bitsize = sizeof(float) * 8;
	eld.componentBitsizes = { bitsize, bitsize, bitsize, bitsize };
	eld.size = 4 * sizeof(float);
	eld.type = VertexComponentType::FLOAT;

	VertexDataElementDescription eldtex;
	eldtex.componentBitsizes = { bitsize, bitsize, bitsize };
	eldtex.size = 3 * sizeof(float);
	eldtex.type = VertexComponentType::FLOAT;

	return Model(std::move(vertexTexCoords.release()), vertexTexCoords.size(), { eld, eldtex }, faces);
}