#ifndef DEVA_FRAMEWORK_GRAPHICS_MODEL_H
#define DEVA_FRAMEWORK_GRAPHICS_MODEL_H

#include "Config.hpp"

#include "VertexBufferObject.hpp"

#include <vector>

namespace DevaFramework 
{


	/**
	------------------------------------------------------------------------------------------
	Model object format specification.

	Size in bytes - description

	4 - Version-dependant signature. If the signature does not match, no parsing will be done.
	4 - 32 bit unsigned integer - Number of vertices in object.
	4 - 32 bit unsigned integer - Number of components per vertex
	4 - 32 bit unsigned integer - Number of VAOs to associate with the object

	------------------------------------------------------------------------------------------
	For each VAO:
	4 - 32 bit unsigned integer - Number of components per vertex for this VAO
	1 - type signature for component data. See 'Type signatures' for more information.

	------------------------------------------------------------------------------------------
	Vertex data:
	Vertex components are listed in sets per VAO.
	For example, consider a simple triangle mesh:

	-1.f, -1.f, +0.f, +1.f, +0.f,  +0.f,
	+1.f, -1.f, +0.f, +1.f, +1.f,  +0.f,
	+0.f, +1.f, +0.f, +1.f, +0.5f, +1.f

	where each vertex consists of 6 components. The first 4 values represent the position vectors,
	and the last 2 values represent texture coordinates. In this case we have 2 VAOs, with 4 and 2 values.
	In .devaobj format this would be layed out as follows:

	//VAO1
	-1.f, -1.f, +0.f, +1.f,
	+1.f, -1.f, +0.f, +1.f,
	+0.f, +1.f, +0.f, +1.f,
	//VAO2
	+0.f,  +0.f,
	+1.f,  +0.f,
	+0.5f, +1.f

	------------------------------------------------------------------------------------------
	Indices:
	4 - 32 bit unsigned integer - Number of elements to draw. Elements are assumed to be \b triangles and hence
	each element has to contain 3 indices.
	1 - Type signature of indices. Accepted types are only DATA_TYPE_INT and DATA_TYPE_UINT, regardless of size

	Index data:
	Every 3 consecutive indices form an element (triangle).

	------------------------------------------------------------------------------------------
	Type signatures:

	A Type signature is a byte, in which:

	The most significant 3 bits denote number type:
	100 - Floating point
	010 - Signed integer
	001 - Unsigned integer

	and the least significant 3 bits denote size:
	001 - 1 byte (8bit)
	010 - 2 bytes (16bit)
	100 - 4 bytes (32bit)

	If the number type is floating-point, then size checks are ignored and size is assumed to be 32bits.
	*/

	class Model {

	public:

		DEVA_FRAMEWORK_API static Model fromFile(const std::string &filename);
		/**TODO: NOT FULLY IMPLEMENTED!!!!!!*/
		DEVA_FRAMEWORK_API static std::vector<byte_t> exportBinary(const Model &model);

	private:
		
		VBO vbo;
		gl::GLenum index_type;
		std::vector<byte_t> indices;

	public:
		DEVA_FRAMEWORK_API Model();
		DEVA_FRAMEWORK_API Model(const VBO &vbo, gl::GLenum index_type, const std::vector<byte_t> &index_arr);

		DEVA_FRAMEWORK_API const VBO& getVBO() const;
		DEVA_FRAMEWORK_API gl::GLenum getIndexType() const;
		DEVA_FRAMEWORK_API const std::vector<byte_t>& getIndexArray() const;

		DEVA_FRAMEWORK_API std::string str();
	};
}


#endif //DEVA_FRAMEWORK_GRAPHICS_MODEL_H
