#ifndef DEVA_FRAMEWORK_UTIL_BYTE_BUFFER_BINARY_WRITER_H
#define DEVA_FRAMEWORK_UTIL_BYTE_BUFFER_BINARY_WRITER_H

#include "Config.hpp"

#include "BinaryWriter.hpp"
#include <vector>

namespace DevaFramework
{
	class ByteBufferBinaryWriter : public BinaryWriter
	{
	private:

		std::vector<char> buffer;
		size_t position;

	public:

		DEVA_UTIL_API ByteBufferBinaryWriter(size_t size);
		DEVA_UTIL_API ByteBufferBinaryWriter(std::vector<char> &&buffer);

		DEVA_UTIL_API ByteBufferBinaryWriter& write(const char* data, size_t count);

		DEVA_UTIL_API void setPosition(size_t new_pos);
		DEVA_UTIL_API size_t getPosition() const;

		DEVA_UTIL_API const std::vector<char>& getBuffer() const;

	};
}

#endif //DEVA_FRAMEWORK_UTIL_BYTE_BUFFER_BINARY_WRITER_H