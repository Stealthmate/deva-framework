#include "BinaryFileStreamWrapper.hpp"

using namespace DevaFramework;

BinaryFileStreamWrapper::BinaryFileStreamWrapper() : BinaryWriter(), stream() {}

BinaryFileStreamWrapper::BinaryFileStreamWrapper(const std::string &path, std::ios_base::openmode openmode) 
	: BinaryWriter(), stream(path, openmode | std::fstream::binary) {}

BinaryFileStreamWrapper& BinaryFileStreamWrapper::write(const char* data, size_t datasize)
{
	stream.write(data, datasize);
	return *this;
}

BinaryFileStreamWrapper& BinaryFileStreamWrapper::read(char* dest, size_t count)
{
	stream.read(dest, count);
	return *this;
}