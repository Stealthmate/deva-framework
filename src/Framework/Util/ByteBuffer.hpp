#ifndef DEVA_FRAMEWORK_UTIL_BYTE_BUFFER_H
#define DEVA_FRAMEWORK_UTIL_BYTE_BUFFER_H

#include "Config.hpp"
#include "../Core/DataHolder.hpp"
#include "ByteOutputStream.hpp"
#include "ByteInputStream.hpp"
#include "Observer.hpp"

#include <vector>
#include <memory>

namespace DevaFramework
{
	class ByteBuffer;

	namespace internal {

		class ByteBufferMessage;

		class ByteBufferViewer : public Observer<ByteBufferMessage> {
		public:

			DEVA_FRAMEWORK_API ByteBufferViewer(std::shared_ptr<ByteBuffer> buffer);
			DEVA_FRAMEWORK_API virtual ~ByteBufferViewer();

			DEVA_FRAMEWORK_API bool valid() const;

			DEVA_FRAMEWORK_API virtual void onNotify(ObservedObject &buffer, const ObservedMessage &message) override;

		protected:

			DEVA_FRAMEWORK_API ByteBuffer& buffer();
			DEVA_FRAMEWORK_API const ByteBuffer& buffer() const;
			DEVA_FRAMEWORK_API void invalidate();
			DEVA_FRAMEWORK_API virtual void revalidate() = 0;
			DEVA_FRAMEWORK_API void destroy();

		private:

			friend class ByteBuffer;

			std::weak_ptr<ByteBuffer> mBuffer;
			bool mValid;
		};
	}
	
	class ByteBuffer : public Observable<internal::ByteBufferMessage>, public DataHolder<std::vector<byte_t>>
	{
	public:

		DEVA_FRAMEWORK_API ByteBuffer();
		DEVA_FRAMEWORK_API ByteBuffer(size_t size);
		DEVA_FRAMEWORK_API ByteBuffer(std::vector<byte_t>&& buffer);
		DEVA_FRAMEWORK_API ByteBuffer(ByteBuffer &&buffer);

		DEVA_FRAMEWORK_API ByteBuffer& operator=(ByteBuffer &&buffer);

		DEVA_FRAMEWORK_API ~ByteBuffer();

		DEVA_FRAMEWORK_API void write(const byte_t * data, size_t count, size_t pos, size_t offset = 0);
		DEVA_FRAMEWORK_API size_t read(byte_t* dest, size_t count, size_t pos, size_t offset = 0) const;

#define READ_TYPE(type) \
	inline void read(type *dest, size_t pos) const { read(reinterpret_cast<byte_t*>(dest), sizeof(type), pos); }
		READ_TYPE(int8_t);
		READ_TYPE(uint8_t);
		READ_TYPE(int16_t);
		READ_TYPE(uint16_t);
		READ_TYPE(int32_t);
		READ_TYPE(uint32_t);
		READ_TYPE(int64_t);
		READ_TYPE(uint64_t);
		READ_TYPE(float_t);
		READ_TYPE(double_t);
#undef READ_TYPE
#define WRITE_TYPE(type) \
	inline void write(type dest, size_t pos) { write(reinterpret_cast<byte_t*>(&dest), sizeof(type), pos); }
		WRITE_TYPE(int8_t);
		WRITE_TYPE(uint8_t);
		WRITE_TYPE(int16_t);
		WRITE_TYPE(uint16_t);
		WRITE_TYPE(int32_t);
		WRITE_TYPE(uint32_t);
		WRITE_TYPE(int64_t);
		WRITE_TYPE(uint64_t);
		WRITE_TYPE(float_t);
		WRITE_TYPE(double_t);
#undef WRITE_TYPE

		DEVA_FRAMEWORK_API size_t size() const;

		DEVA_FRAMEWORK_API void resize(size_t new_size);

		DEVA_FRAMEWORK_API const std::vector<byte_t>& buf() const;

		DEVA_FRAMEWORK_API const ByteBuffer shallowCopy() const;
		DEVA_FRAMEWORK_API ByteBuffer shallowCopy();
		DEVA_FRAMEWORK_API ByteBuffer slice(size_t start, size_t end) const;

	protected:
		DEVA_FRAMEWORK_API virtual std::vector<byte_t> onRelease() override;

	private:

		std::vector<byte_t> buffer;

	};

}

#endif //DEVA_FRAMEWORK_UTIL_BYTE_BUFFER_H
