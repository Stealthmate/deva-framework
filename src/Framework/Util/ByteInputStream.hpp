#ifndef DEVA_FRAMEWORK_UTIL_BINARY_READER_H
#define DEVA_FRAMEWORK_UTIL_BINARY_READER_H

#include "Config.hpp"

namespace DevaFramework
{
	class ByteInputStream
	{
	public:
		DEVA_FRAMEWORK_API virtual size_t read(byte_t* dest, size_t count, size_t offset = 0) = 0;
		DEVA_FRAMEWORK_API virtual size_t available() const = 0;
	};

#define OVERLOAD_OP_EXTRACT(type) \
	inline ByteInputStream& operator >> (ByteInputStream &reader, type &dest) { reader.read(reinterpret_cast<byte_t*>(&dest), sizeof(type)); return reader; };

	OVERLOAD_OP_EXTRACT(int8_t);
	OVERLOAD_OP_EXTRACT(uint8_t);
	OVERLOAD_OP_EXTRACT(int16_t);
	OVERLOAD_OP_EXTRACT(uint16_t);
	OVERLOAD_OP_EXTRACT(int32_t);
	OVERLOAD_OP_EXTRACT(uint32_t);
	OVERLOAD_OP_EXTRACT(int64_t);
	OVERLOAD_OP_EXTRACT(uint64_t);
	OVERLOAD_OP_EXTRACT(float);
	OVERLOAD_OP_EXTRACT(double);
#undef OVERLOAD_OP_EXTRACT
}


#endif //DEVA_FRAMEWORK_UTIL_BINARY_READER_H
