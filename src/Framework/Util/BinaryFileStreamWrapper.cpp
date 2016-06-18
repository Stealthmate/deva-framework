#include "BinaryFileStreamWrapper.hpp"
#include "../Logger.hpp"
using namespace DevaFramework;

BinaryFileStreamWrapper::BinaryFileStreamWrapper() : BinaryWriter(), BinaryReader(), stream() {}

BinaryFileStreamWrapper::BinaryFileStreamWrapper(const std::string &path, std::ios::openmode openmode)
	: BinaryWriter(), BinaryReader(), stream() 
{
	stream.open(path, openmode | std::fstream::binary);
}

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