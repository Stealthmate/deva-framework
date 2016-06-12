#ifndef DEVA_FRAMEWORK_SYSTEM_BINARY_FILE_STREAM_WRITER_H
#define DEVA_FRAMEWORK_SYSTEM_BINARY_FILE_STREAM_WRITER_H

#include "Config.hpp"

#include <fstream>

namespace DevaFramework
{
	class BinaryFileStreamWriter
	{

		std::ofstream output;

	public:

		DEVA_UTIL_API BinaryFileStreamWriter(const std::string &path, std::ios_base::openmode openmode = std::ofstream::out);

		template<typename T>
		DEVA_UTIL_API BinaryFileStreamWriter& write(T data, size_t datasize)
		{
			output.write(reinterpret_cast<const char*>(&data), datasize);
			return *this;
		}

		DEVA_UTIL_API void close();
	};

	inline BinaryFileStreamWriter& operator<<(BinaryFileStreamWriter &os, int8_t data) { return os.write<int8_t>(data, sizeof(int8_t)); };
	inline BinaryFileStreamWriter& operator<<(BinaryFileStreamWriter &os, uint8_t data) { return os.write<uint8_t>(data, sizeof(uint8_t)); };
	inline BinaryFileStreamWriter& operator<<(BinaryFileStreamWriter &os, int16_t data) { return os.write<int16_t>(data, sizeof(int16_t)); };
	inline BinaryFileStreamWriter& operator<<(BinaryFileStreamWriter &os, uint16_t data) { return os.write<uint16_t>(data, sizeof(uint16_t)); };
	inline BinaryFileStreamWriter& operator<<(BinaryFileStreamWriter &os, int32_t data) { return os.write<int32_t>(data, sizeof(int32_t)); };
	inline BinaryFileStreamWriter& operator<<(BinaryFileStreamWriter &os, uint32_t data) { return os.write<uint32_t>(data, sizeof(uint32_t)); };
	inline BinaryFileStreamWriter& operator<<(BinaryFileStreamWriter &os, float data) { return os.write<float>(data, sizeof(float)); };
	inline BinaryFileStreamWriter& operator<<(BinaryFileStreamWriter &os, double data) { return os.write<double>(data, sizeof(double)); };
}

#endif //DEVA_FRAMEWORK_SYSTEM_BINARY_FILE_STREAM_WRITER_H