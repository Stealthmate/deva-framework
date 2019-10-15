#include "BinaryFileStreamWrapper.hpp"

using namespace DevaFramework;

BinaryFileStreamWrapper::BinaryFileStreamWrapper() : ByteOutputStream(), ByteInputStream(), stream() {}

BinaryFileStreamWrapper::BinaryFileStreamWrapper(const std::string &path, std::ios::openmode openmode)
	: ByteOutputStream(), ByteInputStream(), stream() 
{
	stream.open(path, openmode | std::fstream::binary);
}

void BinaryFileStreamWrapper::write(const byte_t* data, size_t datasize, size_t offset)
{
	stream.write((char*)data + offset, datasize);
}

size_t BinaryFileStreamWrapper::read(byte_t* dest, size_t count, size_t offset)
{
	stream.read((char*)dest + offset, count);
#pragma message("TODO: istream reading error check")
	return count;
}