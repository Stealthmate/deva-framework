#ifndef DEVA_FRAMEWORK_UTIL_BINARY_READER_H
#define DEVA_FRAMEWORK_UTIL_BINARY_READER_H

#include "Config.hpp"

namespace DevaFramework
{
	class BinaryReader
	{
	public:
		DEVA_FRAMEWORK_API virtual void read(byte_t* dest, size_t count) = 0;
	};

#define OVERLOAD_OP_EXTRACT(type) \
	inline BinaryReader& operator >> (BinaryReader &reader, type &dest) { reader.read(reinterpret_cast<byte_t*>(&dest), sizeof(type)); return reader; };

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
