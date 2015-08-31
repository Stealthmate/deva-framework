#include "VertexBufferObject.hpp"

#include <glbinding/gl/gl.h>

using namespace DevaFramework;
using namespace gl;

std::string VertexBufferObject::VertexArrayObject::str() const
{
    std::string output = "";
    output+= "  Position: " + strm(id) + "\n";
    output+= "  Loaded: " + strm(loaded) + "\n";
    output+= "  nValuesPerVertex: " + strm(nValuesPerVertex) + "\n";
    output+= "  dataType: " + strm(dataType) + "\n";
    output+= "  spacing:  " + strm(spacing) + "\n";
    output+= "  offset: " + strm((uintptr_t)offset) + "\n";
    return output;
}

VertexBufferObject::VertexArrayObject::VertexArrayObject()
{
    id = 0;
    loaded = false;
    nValuesPerVertex = 3;
    dataType = GL_FLOAT;
    spacing = 0;
    offset = 0;
}

VertexBufferObject::VertexBufferObject()
{
    position = 0;
    data = 0;
    nVertices = 0;
    data_nValues = 0;
    data_byteSize = 0;
    vaos_size = 0;
}

std::string VertexBufferObject::str() const
{
    std::string output;
    output += "\nPosition:      ";
    output +=  strm(position);
    output+= "\nDataptr:       ";
    output+= strm((uintptr_t) data);
    output+= "\nnVertices:     ";
    output+= strm(nVertices);
    output+= "\ndata_nValues:  ";
    output+= strm(data_nValues);
    output+= "\ndata_byteSize: ";
    output+= strm(data_byteSize);
    output+= "\nvaosptr:       ";
    output+= strm((uintptr_t) vaos);
    output+= "\nvaos_size:     ";
    output+= strm((unsigned int) vaos_size);
    for(int i=0;i<=this->vaos_size-1;i++) output+= "\n" +  vaos[i].str();
    output+= "\n";
    return output;
}
