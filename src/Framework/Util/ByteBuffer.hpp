#ifndef DEVA_FRAMEWORK_UTIL_BYTE_BUFFER_H
#define DEVA_FRAMEWORK_UTIL_BYTE_BUFFER_H

#include "Config.hpp"

#include "ByteOutputStream.hpp"
#include "ByteInputStream.hpp"

#include <vector>
#include <memory>

namespace DevaFramework
{
	namespace internal {
		class ByteBufferView;
	}

	class ByteBuffer
	{
	public:

		DEVA_FRAMEWORK_API ByteBuffer();
		DEVA_FRAMEWORK_API ByteBuffer(size_t size);
		DEVA_FRAMEWORK_API ByteBuffer(const std::vector<byte_t> &buffer);
		DEVA_FRAMEWORK_API ~ByteBuffer();

		DEVA_FRAMEWORK_API void write(const byte_t* data, size_t count, size_t offset = 0);
		DEVA_FRAMEWORK_API size_t read(byte_t* dest, size_t count, size_t offset = 0);

		DEVA_FRAMEWORK_API void writeAtPos(const byte_t * data, size_t count, size_t pos, size_t offset = 0);
		DEVA_FRAMEWORK_API size_t readAtPos(byte_t* dest, size_t count, size_t pos, size_t offset = 0) const;

		DEVA_FRAMEWORK_API void setPosition(size_t new_pos);
		DEVA_FRAMEWORK_API size_t getPosition() const;

		DEVA_FRAMEWORK_API size_t size() const;

		DEVA_FRAMEWORK_API void resize(size_t new_size);

		DEVA_FRAMEWORK_API const std::vector<byte_t>& buf() const;
		DEVA_FRAMEWORK_API std::vector<byte_t>& buf();

		DEVA_FRAMEWORK_API const ByteBuffer shallowCopy() const;
		DEVA_FRAMEWORK_API ByteBuffer shallowCopy();
		DEVA_FRAMEWORK_API ByteBuffer slice(size_t start, size_t end) const;

		DEVA_FRAMEWORK_API std::weak_ptr<ByteInputStream> asReadOnly(size_t start = 0, size_t end = 0) const;
		DEVA_FRAMEWORK_API std::weak_ptr<ByteOutputStream> asWriteOnly(size_t start = 0, size_t end = 0, bool autoexpand = false);


	private:

		std::vector<byte_t> buffer;
		size_t position;

		mutable std::vector<std::shared_ptr<internal::ByteBufferView>> viewers;
	};
}

#endif //DEVA_FRAMEWORK_UTIL_BYTE_BUFFER_H
