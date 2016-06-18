#ifndef DEVA_FRAMEWORK_UTIL_BYTE_BUFFER_H
#define DEVA_FRAMEWORK_UTIL_BYTE_BUFFER_H

#include "Config.hpp"

#include "BinaryWriter.hpp"
#include "BinaryReader.hpp"

#include <vector>

namespace DevaFramework
{
	class ByteBuffer : public BinaryWriter, public BinaryReader
	{
	private:

		std::vector<char> buffer;
		size_t position;

	public:

		DEVA_FRAMEWORK_API ByteBuffer(size_t size);
		DEVA_FRAMEWORK_API ByteBuffer(std::vector<char> &&buffer);

		DEVA_FRAMEWORK_API ByteBuffer& write(const char* data, size_t count);
		DEVA_FRAMEWORK_API ByteBuffer& read(char* dest, size_t count);

		DEVA_FRAMEWORK_API void setPosition(size_t new_pos);
		DEVA_FRAMEWORK_API size_t getPosition() const;

		DEVA_FRAMEWORK_API void resize(size_t new_size);

		DEVA_FRAMEWORK_API const std::vector<char>& getBuffer() const;

	};
}

#endif //DEVA_FRAMEWORK_UTIL_BYTE_BUFFER_H