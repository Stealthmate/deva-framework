#ifndef DEVA_FRAMEWORK_UTIL_BINARY_WRITER_H
#define DEVA_FRAMEWORK_UTIL_BINARY_WRITER_H

#include "Config.hpp"

namespace DevaFramework
{
	class BinaryWriter
	{
	public:
		DEVA_FRAMEWORK_API virtual void write(const byte_t* data, size_t count) = 0;
	};

#define OVERLOAD_OP_INSERT(type) \
	inline BinaryWriter& operator<<(BinaryWriter &writer, type data) { writer.write(reinterpret_cast<const byte_t*>(&data), sizeof(type)); return writer; }

	OVERLOAD_OP_INSERT(int8_t);
	OVERLOAD_OP_INSERT(uint8_t);
	OVERLOAD_OP_INSERT(int16_t);
	OVERLOAD_OP_INSERT(uint16_t);
	OVERLOAD_OP_INSERT(int32_t);
	OVERLOAD_OP_INSERT(uint32_t);
	OVERLOAD_OP_INSERT(int64_t);
	OVERLOAD_OP_INSERT(uint64_t);
	OVERLOAD_OP_INSERT(float);
	OVERLOAD_OP_INSERT(double);

#undef OVERLOAD_OP_INSERT
}


#endif //DEVA_FRAMEWORK_UTIL_BINARY_WRITER_H
