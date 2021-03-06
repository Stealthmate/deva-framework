#ifdef DEVA_BUILD_OPENGL

#include "VertexBufferObject.hpp"

#include <glbinding/gl/gl.h>

using namespace DevaFramework;
using namespace gl;

std::string VertexBufferObject::VertexArrayObject::str() const
{
    std::string output = "";
    output+= "  Position: " + str(id) + "\n";
    output+= "  nValuesPerVertex: " + str(nValuesPerVertex) + "\n";
    output+= "  dataType: " + str((int)dataType) + "\n";
    output+= "  stride:  " + str(stride) + "\n";
    output+= "  offset: " + str((uintptr_t)offset) + "\n";
    return output;
}

VertexBufferObject::VertexArrayObject::VertexArrayObject()
	: id(0), nValuesPerVertex(0), dataType(gl::GLenum::GL_NONE), stride(0), offset(0) {}

VertexBufferObject::VertexArrayObject::VertexArrayObject(
	gl::GLuint id,
	gl::GLuint nValuesPerVertex,
	gl::GLenum dataType,
	gl::GLsizei stride,
	uintptr_t offset) : id(id), nValuesPerVertex(nValuesPerVertex), dataType(dataType), stride(stride), offset(offset) {}

VertexBufferObject::VertexBufferObject() : data(), nVertices(0), data_nValues(0), data_byteSize(0), vaos(), vaos_size(0) {}
VertexBufferObject::VertexBufferObject(
	const std::vector<byte_t> &data,
	gl::GLuint nVertices,
	gl::GLuint data_nValues,
	gl::GLuint data_byteSize,
	const std::vector<VertexArrayObject> &vaos,
	unsigned int vaos_size) 
	: data(data), nVertices(nVertices), data_nValues(data_nValues), data_byteSize(data_byteSize), vaos(vaos), vaos_size(vaos_size) {}

std::string VertexBufferObject::str() const
{
    std::string output;
    output+= "\nDataptr:       ";
    output+= str((uintptr_t) &data[0]);
    output+= "\nnVertices:     ";
    output+= str(nVertices);
    output+= "\ndata_nValues:  ";
    output+= str(data_nValues);
    output+= "\ndata_byteSize: ";
    output+= str(data_byteSize);
    output+= "\nvaosptr:       ";
    output+= str((uintptr_t) &vaos[0]);
    output+= "\nvaos_size:     ";
    output+= str((unsigned int) vaos_size);
    for(unsigned int i=0;i<=this->vaos_size-1;i++) output+= "\n" +  vaos[i].str();
    output+= "\n";
    return output;
}

#endif // DEVA_BUILD_OPENGL
