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

		std::vector<byte_t> buffer;
		size_t position;

	public:

		ByteBuffer() : buffer(0), position(0) {}
		DEVA_FRAMEWORK_API ByteBuffer(size_t size);
		DEVA_FRAMEWORK_API ByteBuffer(const std::vector<byte_t> &buffer);

		DEVA_FRAMEWORK_API virtual void write(const byte_t* data, size_t count) override;
		DEVA_FRAMEWORK_API virtual void read(byte_t* dest, size_t count) override;

		DEVA_FRAMEWORK_API void setPosition(size_t new_pos);
		DEVA_FRAMEWORK_API size_t getPosition() const;

		DEVA_FRAMEWORK_API size_t size() const;

		DEVA_FRAMEWORK_API void resize(size_t new_size);

		DEVA_FRAMEWORK_API const std::vector<byte_t>& buf() const;
		DEVA_FRAMEWORK_API std::vector<byte_t>& buf();

	};
}

#endif //DEVA_FRAMEWORK_UTIL_BYTE_BUFFER_H
