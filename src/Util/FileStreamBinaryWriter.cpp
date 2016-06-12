#include "FileStreamBinaryWriter.hpp"

using namespace DevaFramework;

FileStreamBinaryWriter::FileStreamBinaryWriter() : BinaryWriter(), output() {}

FileStreamBinaryWriter::FileStreamBinaryWriter(const std::string &path, std::ios_base::openmode openmode) : BinaryWriter(), output()
{
	this->open(path, openmode);
}

void FileStreamBinaryWriter::open(const std::string &path, std::ios_base::openmode openmode)
{
	output.open(path, openmode | std::ofstream::binary);
}

void FileStreamBinaryWriter::close()
{
	output.close();
}

FileStreamBinaryWriter& FileStreamBinaryWriter::write(const char* data, size_t datasize)
{
	output.write(data, datasize);
	return *this;
}