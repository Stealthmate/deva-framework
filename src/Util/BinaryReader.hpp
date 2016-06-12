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

	inline BinaryReader& operator>>(BinaryReader &reader, int8_t &dest) { return reader.read(reinterpret_cast<char*>(&dest), sizeof(int8_t)); };
	inline BinaryReader& operator>>(BinaryReader &reader, uint8_t &dest) { return reader.read(reinterpret_cast<char*>(&dest), sizeof(uint8_t)); };
	inline BinaryReader& operator>>(BinaryReader &reader, int16_t &dest) { return reader.read(reinterpret_cast<char*>(&dest), sizeof(int16_t)); };
	inline BinaryReader& operator>>(BinaryReader &reader, uint16_t &dest) { return reader.read(reinterpret_cast<char*>(&dest), sizeof(uint16_t)); };
	inline BinaryReader& operator>>(BinaryReader &reader, int32_t &dest) { return reader.read(reinterpret_cast<char*>(&dest), sizeof(int32_t)); };
	inline BinaryReader& operator>>(BinaryReader &reader, uint32_t &dest) { return reader.read(reinterpret_cast<char*>(&dest), sizeof(uint32_t)); };
	inline BinaryReader& operator>>(BinaryReader &reader, float &dest) { return reader.read(reinterpret_cast<char*>(&dest), sizeof(float)); };
	inline BinaryReader& operator>>(BinaryReader &reader, double &dest) { return reader.read(reinterpret_cast<char*>(&dest), sizeof(double)); };
}


#endif //DEVA_FRAMEWORK_UTIL_BINARY_READER_H