#ifndef DEVA_FRAMEWORK_UTIL_BINARY_WRITER_H
#define DEVA_FRAMEWORK_UTIL_BINARY_WRITER_H

#include "Config.hpp"

namespace DevaFramework
{
	class BinaryWriter
	{
	public:
		DEVA_UTIL_API virtual BinaryWriter& write(const char* data, size_t count) = 0;
	};

	inline BinaryWriter& operator<<(BinaryWriter &os, int8_t data) { return os.write(reinterpret_cast<const char*>(&data), sizeof(int8_t)); };
	inline BinaryWriter& operator<<(BinaryWriter &os, uint8_t data) { return os.write(reinterpret_cast<const char*>(&data), sizeof(uint8_t)); };
	inline BinaryWriter& operator<<(BinaryWriter &os, int16_t data) { return os.write(reinterpret_cast<const char*>(&data), sizeof(int16_t)); };
	inline BinaryWriter& operator<<(BinaryWriter &os, uint16_t data) { return os.write(reinterpret_cast<const char*>(&data), sizeof(uint16_t)); };
	inline BinaryWriter& operator<<(BinaryWriter &os, int32_t data) { return os.write(reinterpret_cast<const char*>(&data), sizeof(int32_t)); };
	inline BinaryWriter& operator<<(BinaryWriter &os, uint32_t data) { return os.write(reinterpret_cast<const char*>(&data), sizeof(uint32_t)); };
	inline BinaryWriter& operator<<(BinaryWriter &os, float data) { return os.write(reinterpret_cast<const char*>(&data), sizeof(float)); };
	inline BinaryWriter& operator<<(BinaryWriter &os, double data) { return os.write(reinterpret_cast<const char*>(&data), sizeof(double)); };
}


#endif //DEVA_FRAMEWORK_UTIL_BINARY_WRITER_H