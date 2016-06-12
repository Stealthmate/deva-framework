#ifndef DEVA_FRAMEWORK_UTIL_FILE_STREAM_BINARY_WRITER_H
#define DEVA_FRAMEWORK_UTIL_FILE_STREAM_BINARY_WRITER_H

#include "Config.hpp"

#include "BinaryWriter.hpp"

#include <fstream>

namespace DevaFramework
{
	class FileStreamBinaryWriter : public BinaryWriter
	{
		std::ofstream output;
	public:

		DEVA_UTIL_API FileStreamBinaryWriter();
		DEVA_UTIL_API FileStreamBinaryWriter(const std::string &path, std::ios_base::openmode openmode = std::ofstream::out);

		DEVA_UTIL_API FileStreamBinaryWriter& write(const char* data, size_t count);		
		
		DEVA_UTIL_API void open(const std::string &path, std::ios_base::openmode openmode = std::ofstream::out);
		DEVA_UTIL_API void close();
	};
}

#endif //DEVA_FRAMEWORK_UTIL_FILE_STREAM_BINARY_WRITER_H