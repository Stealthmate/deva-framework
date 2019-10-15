#ifndef DEVA_FRAMEWORK_UTIL_BINARY_FILE_STREAM_WRAPPER_H
#define DEVA_FRAMEWORK_UTIL_BINARY_FILE_STREAM_WRAPPER_H

#include "Config.hpp"

#include "ByteOutputStream.hpp"
#include "ByteInputStream.hpp"

#include <fstream>

namespace DevaFramework
{
	class BinaryFileStreamWrapper: public ByteOutputStream, public ByteInputStream
	{
	public:
		std::fstream stream;

		DEVA_FRAMEWORK_API BinaryFileStreamWrapper();
		DEVA_FRAMEWORK_API BinaryFileStreamWrapper(const std::string &path, std::ios::openmode openmode = std::ios::in);

		DEVA_FRAMEWORK_API virtual void write(const byte_t* data, size_t count, size_t offset = 0) override;
		DEVA_FRAMEWORK_API virtual size_t read(byte_t* data, size_t count, size_t offset = 0) override;
	};
}

#endif //DEVA_FRAMEWORK_UTIL_BINARY_FILE_STREAM_WRAPPER_H
