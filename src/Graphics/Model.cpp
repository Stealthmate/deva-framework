#include "Model.hpp"

#include <fstream>

#include "../System/Exceptions.hpp"
#include "../System/Logger.hpp"

#include "../Util/ByteBuffer.hpp"
#include "../Util/BinaryFileStreamWrapper.hpp"

using namespace DevaFramework;

static const int32_t SERIALID = 102;

static const char DATA_TYPE_FLOAT = (char)0b10000000;
static const char DATA_TYPE_INT   = (char)0b01000000;
static const char DATA_TYPE_UINT  = (char)0b00100000;

static const char DATA_SIZE_8  = (char)0b00000001;
static const char DATA_SIZE_16 = (char)0b00000010;
static const char DATA_SIZE_32 = (char)0b00000100;

static const char DATA_SIZE_MASK = 0b000000111;

static const int INDICES_PER_ELEMENT = 3;


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

	BinaryFileStreamWrapper bfsw = BinaryFileStreamWrapper(filename, std::ios::in);
	std::fstream &file_input = bfsw.stream;

	if (!file_input.is_open()) throw DevaInvalidInputException("Cannot load model. Invalid file name (cannot open file).");

	int32_t n_vertices;
	int32_t n_components;
	int32_t n_vao;
	std::vector<int32_t> n_components_vao;
	std::vector<int8_t> component_type_vao;

	int32_t serial_id;
	bfsw >> serial_id;
	if (serial_id != SERIALID) 
		throw DevaInvalidInputException("Cannot load model. Serial ID does not match current version. (file id: " + strm(serial_id) + ")");

	bfsw >> n_vertices;
	bfsw >> n_components;
	bfsw >> n_vao;

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
		bfsw >> n_components_vao[i];
		bfsw >> (int8_t)component_type_vao[i];

		VAO vao;
		vao.id = i;
		vao.nValuesPerVertex = n_components_vao[i];
		vao.spacing = 0;
		vao.dataType = getGLType(component_type_vao[i]);

		vao_bytesize = (component_type_vao[i] & DATA_SIZE_MASK) * n_components_vao[i] * n_vertices;


		bytesize += vao_bytesize;
		vao.offset = bytesize - vao_bytesize;
		vaos.push_back(vao);
	}

	vbo.vaos = vaos;
	vbo.data_byteSize = bytesize;
	std::vector<char> data;
	data.resize(vbo.data_byteSize);
	bfsw.read(&data[0], vbo.data_byteSize);

	vbo.data = data;

	int32_t n_elements;
	bfsw >> n_elements;

	int8_t index_type;
	bfsw >> index_type;

	if (!(index_type & DATA_TYPE_INT || index_type & DATA_TYPE_UINT))
		throw DevaInvalidInputException("Cannot load model. Bad index type. (type: " + strm((int)index_type) + ")");

	std::vector<char> index_data;
	index_data.resize(n_elements * INDICES_PER_ELEMENT * (index_type & DATA_SIZE_MASK));

	bfsw.read((char*)(&index_data[0]), n_elements * INDICES_PER_ELEMENT * (index_type & DATA_SIZE_MASK));

	return Model(vbo, getGLType(index_type), index_data);
}

std::vector<char> Model::exportBinary(const Model &model)
{

	int nVertices = model.vbo.nVertices;
	int data_byteSize = model.vbo.data_byteSize;
	int n_comp_vert = model.vbo.data_nValues / nVertices;
	int n_vaos = model.vbo.vaos_size;

	int index_arr_size = (int)model.indices.size();
	int8_t index_type = getToken(model.index_type);

	ByteBuffer buffer = ByteBuffer(16 + (n_vaos * 5) + data_byteSize + 5 + index_arr_size + 1);

	buffer << SERIALID << nVertices << n_comp_vert << n_vaos;

	for (int i = 0;i <= n_vaos - 1;i++)
	{
		buffer << model.vbo.vaos[i].nValuesPerVertex << getToken(model.vbo.vaos[i].dataType);
	}
	auto data = model.vbo.data;
	for (int i = 0;i <= n_vaos - 1;i++)
	{
		int step = model.vbo.vaos[i].spacing;
		uintptr_t offset = model.vbo.vaos[i].offset;
		int compsize = getToken(model.vbo.vaos[i].dataType) & DATA_SIZE_MASK;
		int comps = model.vbo.vaos[i].nValuesPerVertex;
		for (int j = 0; j <= nVertices - 1; j++)
		{
			for (int v = 0; v <= comps - 1;v++)
			{
				for (int k = 0;k <= compsize - 1;k++)
				{
					buffer << (int8_t)data[offset + (j*step) + (v*compsize) + k];
				}
			}
		}
	}

	buffer << index_arr_size / ((index_type & DATA_SIZE_MASK)*INDICES_PER_ELEMENT);
	buffer << (int8_t)index_type;
	buffer.write(&model.indices[0], model.indices.size());
	return buffer.getBuffer();
}

Model::Model() : vbo(), index_type(gl::GL_INT), indices() {}

Model::Model(const VBO &vbo, gl::GLenum index_type, const std::vector<char> &indices) : vbo(vbo), index_type(index_type), indices(indices) {}

const VBO& Model::getVBO() const
{
	return this->vbo;
}

gl::GLenum Model::getIndexType() const
{
	return this->index_type;
}

const std::vector<char>& Model::getIndexArray() const
{
	return this->indices;
}