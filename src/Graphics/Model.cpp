#include "Model.hpp"

#include <fstream>

#include "../System/Exceptions.hpp"
#include "../System/Logger.hpp"

using namespace DevaFramework;

static const int32_t SERIALID = 100;

static const char DATA_TYPE_FLOAT = 0b00000001;
static const char DATA_TYPE_INT   = 0b00000010;
static const char DATA_TYPE_UINT  = 0b00000100;

static const char DATA_SIZE_8  = 0b10000000;
static const char DATA_SIZE_16 = 0b01000000;
static const char DATA_SIZE_32 = 0b00100000;


static gl::GLenum getGLType(int8_t token) 
{
	if (false);
	else if (token & DATA_TYPE_FLOAT) return gl::GL_FLOAT;
	else if (token & DATA_TYPE_INT)
	{
		if (false);
		else if (token & DATA_SIZE_8) return gl::GL_BYTE;
		else if (token & DATA_SIZE_16) return gl::GL_SHORT;
		else if (token & DATA_SIZE_32) return gl::GL_INT;
		else throw DevaInvalidInputException("Cannot load model. Invalid data type.");
	}
	else if (token & DATA_TYPE_UINT)
	{
		if (false);
		else if (token & DATA_SIZE_8) return gl::GL_UNSIGNED_BYTE;
		else if (token & DATA_SIZE_16) return gl::GL_UNSIGNED_SHORT;
		else if (token & DATA_SIZE_32) return gl::GL_UNSIGNED_INT;
		else throw DevaInvalidInputException("Cannot load model. Invalid data type.");
	}
	else throw DevaInvalidInputException("Cannot load model. Invalid data type.");
}

static int8_t getToken(gl::GLenum type)
{
	switch (type)
	{
	case gl::GL_FLOAT: return DATA_TYPE_FLOAT | DATA_SIZE_32;
	case gl::GL_BYTE: return DATA_TYPE_INT | DATA_SIZE_8;
	case gl::GL_UNSIGNED_BYTE: return DATA_TYPE_UINT | DATA_SIZE_8;
	case gl::GL_SHORT: return DATA_TYPE_INT | DATA_SIZE_16;
	case gl::GL_UNSIGNED_SHORT: return DATA_TYPE_UINT | DATA_SIZE_16;
	case gl::GL_INT: return DATA_TYPE_INT | DATA_SIZE_32;
	case gl::GL_UNSIGNED_INT: return DATA_TYPE_UINT | DATA_SIZE_32;
	default: throw DevaInvalidInputException("Requested token for invalid GL type (" + strm(type) + ")");
	}
}

Model Model::fromFile(const std::string &filename) {

	std::ifstream file_input;
	file_input.open(filename, std::ifstream::in | std::ifstream::binary);

	if (!file_input.is_open()) throw DevaInvalidInputException("Cannot load model. Invalid file name (cannot open file).");

	int32_t n_vertices;
	int8_t n_components;
	int8_t n_vao;
	std::vector<int8_t> n_components_vao;
	std::vector<int8_t> component_type_vao;

	int32_t serial_id;
	file_input.read(reinterpret_cast<char*>(&serial_id), 4);
	if (serial_id != SERIALID) throw DevaInvalidInputException("Cannot load model. Serial ID does not match current version. (file id: " + strm(serial_id) + ")");

	file_input.read(reinterpret_cast<char*>(&n_vertices), 4);
	file_input.read(reinterpret_cast<char*>(&n_components), 1);
	file_input.read(reinterpret_cast<char*>(&n_vao), 1);

	VBO vbo;
	vbo.nVertices = n_vertices;
	vbo.data_nValues = n_vertices * n_components;
	vbo.vaos_size = n_vao;

	n_components_vao.resize(n_vao, 0);
	component_type_vao.resize(n_vao, 0);

	std::vector<VAO> vaos;

	int bytesize = 0;
	int vao_bytesize = 0;
	for (int i = 0; i <= n_vao - 1;i++) 
	{
		file_input.read(reinterpret_cast<char*>(&n_components_vao[i]), 1);
		file_input.read(reinterpret_cast<char*>(&component_type_vao[i]), 1);

		VAO vao;
		vao.id = i;
		vao.nValuesPerVertex = n_components_vao[i];
		vao.spacing = 0;
		vao.dataType = getGLType(component_type_vao[i]);

		if (component_type_vao[i] & DATA_SIZE_8)      vao_bytesize = 1 * n_components_vao[i];
		else if (component_type_vao[i] & DATA_SIZE_16) vao_bytesize = 2 * n_components_vao[i];
		else if (component_type_vao[i] & DATA_SIZE_32) vao_bytesize = 4 * n_components_vao[i];


		bytesize += vao_bytesize;
		vao.offset = bytesize - vao_bytesize;
		vaos.push_back(vao);
	}

	vbo.vaos = vaos;
	vbo.data_byteSize = bytesize * n_vertices;
	std::vector<char> data;
	data.resize(vbo.data_byteSize);

	file_input.read(&data[0], vbo.data_byteSize);
	
	vbo.data = data;

	int32_t n_elements;
	file_input.read(reinterpret_cast<char*>(&n_elements), 4);
	std::vector<uint16_t> indices;
	indices.resize(n_elements * 3);

	file_input.read((char*)(&indices[0]), n_elements * 3 * 2);

	Model model = Model(vbo, indices);

	return model;
}

/*std::vector<char> Model::exportBinary(const Model &model)
{
	std::vector<char> binary;

	int nVertices = model.vbo.nVertices;
	int data_byteSize = model.vbo.data_byteSize;
	int n_vaos = model.vbo.vaos_size;

	std::vector<int8_t> n_components_vao;
	std::vector<int8_t> component_type_vao;

	for (int i = 0;i <= n_vaos - 1;i++)
	{
		n_components_vao.push_back(model.vbo.vaos[i].nValuesPerVertex);
		component_type_vao.push_back(getToken(model.vbo.vaos[i].dataType));
	}
}*/

Model::Model() : vbo(), index_arr() {}

Model::Model(const VBO &vbo, const std::vector<uint16_t> &index_arr) : vbo(vbo), index_arr(index_arr) {}

const VBO& Model::getVBO() const
{
	return this->vbo;
}

const std::vector<uint16_t>& Model::getIndexArray() const
{
	return this->index_arr;
}