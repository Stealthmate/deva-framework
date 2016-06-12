#ifndef DEVA_FRAMEWORK_UTIL_BINARY_READER_H
#define DEVA_FRAMEWORK_UTIL_BINARY_READER_H

#include "Config.hpp"

namespace DevaFramework
{
	class BinaryReader
	{
	public:
		DEVA_UTIL_API virtual BinaryReader& read(char* dest, size_t count) = 0;
	};

	inline BinaryReader& operator>>(BinaryReader &os, int8_t dest) { return os.read(reinterpret_cast<char*>(&dest), sizeof(int8_t)); };
	inline BinaryReader& operator>>(BinaryReader &os, uint8_t dest) { return os.read(reinterpret_cast<char*>(&dest), sizeof(uint8_t)); };
	inline BinaryReader& operator>>(BinaryReader &os, int16_t dest) { return os.read(reinterpret_cast<char*>(&dest), sizeof(int16_t)); };
	inline BinaryReader& operator>>(BinaryReader &os, uint16_t dest) { return os.read(reinterpret_cast<char*>(&dest), sizeof(uint16_t)); };
	inline BinaryReader& operator>>(BinaryReader &os, int32_t dest) { return os.read(reinterpret_cast<char*>(&dest), sizeof(int32_t)); };
	inline BinaryReader& operator>>(BinaryReader &os, uint32_t dest) { return os.read(reinterpret_cast<char*>(&dest), sizeof(uint32_t)); };
	inline BinaryReader& operator>>(BinaryReader &os, float dest) { return os.read(reinterpret_cast<char*>(&dest), sizeof(float)); };
	inline BinaryReader& operator>>(BinaryReader &os, double dest) { return os.read(reinterpret_cast<char*>(&dest), sizeof(double)); };
}


#endif //DEVA_FRAMEWORK_UTIL_BINARY_READER_H