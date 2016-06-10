#ifndef DEVA_FRAMEWORK_GRAPHICS_MODEL_H
#define DEVA_FRAMEWORK_GRAPHICS_MODEL_H

#include "Config.hpp"

#include "VertexBufferObject.hpp"

#include <vector>

namespace DevaFramework 
{
	class Model {

	public:

		DEVA_GRAPHICS_API static Model fromFile(const std::string &filename);
		DEVA_GRAPHICS_API static std::vector<char> exportBinary(const Model &model);

	private:
		
		VBO vbo;

		std::vector<unsigned int> index_arr;

	public:
		DEVA_GRAPHICS_API Model();
		DEVA_GRAPHICS_API Model(const VBO &vbo, const std::vector<unsigned int> &index_arr);

		DEVA_GRAPHICS_API const VBO& getVBO() const;
		DEVA_GRAPHICS_API const std::vector<unsigned int>& getIndexArray() const;

		DEVA_GRAPHICS_API std::string str();
	};
}


#endif //DEVA_FRAMEWORK_GRAPHICS_MODEL_H