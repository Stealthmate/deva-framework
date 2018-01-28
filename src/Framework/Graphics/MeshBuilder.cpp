#include "MeshBuilder.hpp"
#include "Mesh.hpp"

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
	this->vertices.push_back({ vertex[0], vertex[1], vertex[2], vertex[3] });
	return *this;
}

BasicModelBuilder& BasicModelBuilder::addFace(const uvec3 &face)
{
	this->faces.push_back(face);
	return *this;
}

Mesh BasicModelBuilder::build() const
{
	size_t vert_size = vertices.size() * 4 * sizeof(float);
	size_t face_size = faces.size() * 3 * sizeof(uint32_t);
	std::vector<byte_t> data(vert_size + face_size);
	data.resize(vert_size + face_size);

	for (int i = 0;i < vertices.size();i++) {
		auto raw = vertices[i].rawData();
		std::memcpy(&data[i * raw.second], raw.first, raw.second);
	}
	for (int i = 0;i < faces.size();i++) {
		auto raw = faces[i].rawData();
		std::memcpy(&data[vert_size + (i * raw.second)], raw.first, raw.second);
	}

	VertexDataElementDescription eld;
	size_t bitsize = sizeof(float) * 8;
	eld.componentBitsizes = { bitsize, bitsize, bitsize, bitsize };
	eld.size = 4 * sizeof(float);
	eld.type = VertexComponentType::FLOAT;

	return Mesh(data, vertices.size(), { eld });
}

TexturedModelBuilder& TexturedModelBuilder::addVertex(const vec4 &vertex, const vec3 &tex) {
	vertices.push_back(vertex);
	texCoords.push_back(tex);
	return *this;
}

TexturedModelBuilder&::TexturedModelBuilder::addFace(const uvec3 &face)
{
	this->faces.push_back(face);
	return *this;
}

Mesh TexturedModelBuilder::build()
{
	size_t vert_size = vertices.size() * 4 * sizeof(float);
	size_t tex_size = texCoords.size() * 3 * sizeof(float);
	size_t face_size = faces.size() * 3 * sizeof(uint32_t);


	std::vector<byte_t> data(vert_size + tex_size + face_size);
	data.resize(vert_size + tex_size + face_size);

	size_t stride = 7 * sizeof(float);
	for (auto i = 0;i < vertices.size();i++) {
		auto rawv = vertices[i].rawData();
		std::memcpy(data.data() + (i * stride), (byte_t*)rawv.first, rawv.second * sizeof(float));
		auto rawt = texCoords[i].rawData();
		std::memcpy(data.data() + (i * stride) + (rawv.second*sizeof(float)), (byte_t*)rawt.first, rawt.second * sizeof(float));
	}
	/*
	for (int i = 0;i < vertices.size();i++) {
		auto raw = vertices[i].rawData();
		std::memcpy(&data[i * raw.second], raw.first, raw.second);
	}

	for (int i = 0;i < texCoords.size();i++) {
		auto raw = texCoords[i].rawData();
		std::memcpy(&data[vert_size + (i * raw.second)], raw.first, raw.second);
	}
	*/
	for (int i = 0;i < faces.size();i++) {
		auto raw = faces[i].rawData();
		std::memcpy(&data[vert_size + tex_size + (i * raw.second * sizeof(uint32_t))], raw.first, raw.second * sizeof(uint32_t));
	}

	VertexDataElementDescription eld;
	size_t bitsize = sizeof(float) * 8;
	eld.componentBitsizes = { bitsize, bitsize, bitsize, bitsize };
	eld.size = 4 * sizeof(float);
	eld.type = VertexComponentType::FLOAT;

	VertexDataElementDescription eldtex;
	eldtex.componentBitsizes = { bitsize, bitsize, bitsize };
	eldtex.size = 3 * sizeof(float);
	eldtex.type = VertexComponentType::FLOAT;

	return Mesh(data, vertices.size(), { eld, eldtex });
}