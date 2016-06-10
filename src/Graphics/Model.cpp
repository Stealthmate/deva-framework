#include "Model.hpp"

#include <fstream>

#include "../System/Exceptions.hpp"

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
	file_input >> serial_id;
	if (serial_id != SERIALID) throw DevaInvalidInputException("Cannot load model. Serial ID does not match current version.");

	file_input >> n_vertices >> n_components >> n_vao;

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
		file_input >> n_components_vao[i] >> component_type_vao[i];

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

	}

	vbo.vaos = vaos;
	vbo.data_byteSize = bytesize;
	std::vector<char> data;
	data.resize(vbo.data_byteSize);

	file_input.read(&data[0], bytesize);
	
	vbo.data = data;

	int32_t n_elements;
	file_input >> n_elements;

	std::vector<uint32_t> indices;
	indices.resize(n_elements * 3);

	file_input.read((char*)(&indices[0]), n_elements * 3 * 4);

	Model model = Model(vbo, indices);

	return model;
}

Model::Model() : vbo(), index_arr() {}

Model::Model(const VBO &vbo, const std::vector<unsigned int> &index_arr) : vbo(vbo), index_arr(index_arr) {}