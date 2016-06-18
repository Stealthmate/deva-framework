#ifndef DEVA_FRAMEWORK_UTIL_BINARY_FILE_STREAM_WRAPPER_H
#define DEVA_FRAMEWORK_UTIL_BINARY_FILE_STREAM_WRAPPER_H

#include "Config.hpp"

#include "BinaryWriter.hpp"
#include "BinaryReader.hpp"

#include <fstream>

namespace DevaFramework
{
	class BinaryFileStreamWrapper: public BinaryWriter, public BinaryReader
	{
	public:
		std::fstream stream;

		DEVA_FRAMEWORK_API BinaryFileStreamWrapper();
		DEVA_FRAMEWORK_API BinaryFileStreamWrapper(const std::string &path, std::ios::openmode openmode = std::ios::in);

		DEVA_FRAMEWORK_API BinaryFileStreamWrapper& write(const char* data, size_t count);
		DEVA_FRAMEWORK_API BinaryFileStreamWrapper& read(char* data, size_t count);
	};
}

#endif //DEVA_FRAMEWORK_UTIL_BINARY_FILE_STREAM_WRAPPER_H