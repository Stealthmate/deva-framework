#ifndef DEVA_FRAMEWORK_UTIL_BYTE_BUFFER_STREAM_HPP
#define DEVA_FRAMEWORK_UTIL_BYTE_BUFFER_STREAM_HPP

#include "Config.hpp"

#include "ByteBuffer.hpp"

namespace DevaFramework {

	namespace internal {
		class ByteBufferStreamBase : public ByteBuffer::ByteBufferViewer {
		public:

			ByteBufferStreamBase(std::shared_ptr<ByteBuffer> buffer);
			DEVA_FRAMEWORK_API virtual ~ByteBufferStreamBase();

			DEVA_FRAMEWORK_API void setPosition(size_t pos);
			DEVA_FRAMEWORK_API size_t getPosition() const;

		protected:

			size_t position;
		};
	}

	class ByteBufferInputStream : public internal::ByteBufferStreamBase, public ByteInputStream {
	public:
		DEVA_FRAMEWORK_API ByteBufferInputStream(std::shared_ptr<ByteBuffer> buffer);
		DEVA_FRAMEWORK_API virtual ~ByteBufferInputStream();

		DEVA_FRAMEWORK_API virtual size_t read(byte_t* dest, size_t count, size_t offset = 0);
		DEVA_FRAMEWORK_API virtual size_t available() const;
	};

	class ByteBufferOutputStream : public internal::ByteBufferStreamBase, public ByteOutputStream {
	public:
		DEVA_FRAMEWORK_API ByteBufferOutputStream(std::shared_ptr<ByteBuffer> buffer);
		DEVA_FRAMEWORK_API virtual ~ByteBufferOutputStream();

		DEVA_FRAMEWORK_API virtual void write(const byte_t* data, size_t count, size_t offset = 0);
	};
}


#endif //DEVA_FRAMEWORK_UTIL_BYTE_BUFFER_STREAM_HPP