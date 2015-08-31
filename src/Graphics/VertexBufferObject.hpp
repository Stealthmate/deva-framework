#ifndef DEVA_FRAMEWORK_GRAPHICS_OPENGL_VERTEX_BUFFER_OBJECT_H
#define DEVA_FRAMEWORK_GRAPHICS_OPENGL_VERTEX_BUFFER_OBJECT_H

#include "Config.hpp"

#include <glbinding/gl/gl.h>

namespace DevaFramework
{

///Stores information about a Vertex Buffer Object, along with its underlying Vertex Array Objects
struct VertexBufferObject
{
    ///Stores information about a Vertex Array Object
    struct VertexArrayObject
    {
        ///The AttribPointer of the VAO
        gl::GLuint id;
        bool loaded;
        ///The number of values stored for each vertex
		gl::GLuint nValuesPerVertex;
        ///The type of values stored
		gl::GLenum dataType;
        ///The amount of bytes between each individual value
        char spacing;
        ///The offset in bytes, from the beginning of the buffer, where the array begins
        void* offset;

        VertexArrayObject();

        std::string str() const;

    };

    ///The position of the buffer, provided by OpenGL
	gl::GLuint position;
    ///The raw data to be copied in the buffer
    void* data;
    ///The number of vertices, for which information is stored
	gl::GLuint nVertices;
    ///The number of values to be stored
	gl::GLuint data_nValues;
    ///The size of the buffer to be allocated
	gl::GLuint data_byteSize;
    ///A pointer to an array of VertexArrayObject objects, in which information about each VAO is stored
    VertexArrayObject* vaos;
    ///The number of VAOs stored
    char vaos_size;

    VertexBufferObject();

    std::string str() const;
};

typedef VertexBufferObject VBO;
typedef VBO::VertexArrayObject VAO;

}

#endif //DEVA_FRAMEWORK_GRAPHICS_OPENGL_VERTEX_BUFFER_OBJECT_H
