#ifndef DEVA_FRAMEWORK_GRAPHICS_OPENGL_VERTEX_BUFFER_OBJECT_H
#define DEVA_FRAMEWORK_GRAPHICS_OPENGL_VERTEX_BUFFER_OBJECT_H

#include "Config.hpp"

#include <glbinding/gl/gl.h>

#include <vector>

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
        ///The number of values stored for each vertex
		gl::GLuint nValuesPerVertex;
        ///The type of values stored
		gl::GLenum dataType;
        ///The amount of bytes between each individual vertex component set
        gl::GLsizei stride;
        ///The offset in bytes, from the beginning of the buffer, where the array begins
        uintptr_t offset;

		DEVA_FRAMEWORK_API VertexArrayObject();
		DEVA_FRAMEWORK_API VertexArrayObject(
			gl::GLuint id, 
			gl::GLuint nValuesPerVertex, 
			gl::GLenum dataType, 
			gl::GLsizei stride, 
			uintptr_t offset);

        std::string str() const;

    };

    ///The raw data to be copied in the buffer
	std::vector<char> data;
    ///The number of vertices, for which information is stored
	gl::GLuint nVertices;
    ///The number of values to be stored
	gl::GLuint data_nValues;
    ///The size of the buffer to be allocated
	gl::GLuint data_byteSize;
    ///A pointer to an array of VertexArrayObject objects, in which information about each VAO is stored
	std::vector<VertexArrayObject> vaos;
    ///The number of VAOs stored
    unsigned int vaos_size;

	DEVA_FRAMEWORK_API VertexBufferObject();
	DEVA_FRAMEWORK_API VertexBufferObject(
		const std::vector<char> &data, 
		gl::GLuint nVertices, 
		gl::GLuint data_nValues, 
		gl::GLuint data_byteSize,
		const std::vector<VertexArrayObject> &vaos,
		unsigned int vaos_size);

    DEVA_FRAMEWORK_API std::string str() const;
};

typedef VertexBufferObject VBO;
typedef VBO::VertexArrayObject VAO;

}

#endif //DEVA_FRAMEWORK_GRAPHICS_OPENGL_VERTEX_BUFFER_OBJECT_H
