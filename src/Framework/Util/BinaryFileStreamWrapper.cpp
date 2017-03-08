#include "BinaryFileStreamWrapper.hpp"

using namespace DevaFramework;

BinaryFileStreamWrapper::BinaryFileStreamWrapper() : BinaryWriter(), BinaryReader(), stream() {}

BinaryFileStreamWrapper::BinaryFileStreamWrapper(const std::string &path, std::ios::openmode openmode)
	: BinaryWriter(), BinaryReader(), stream() 
{
	stream.open(path, openmode | std::fstream::binary);
}

void BinaryFileStreamWrapper::write(const byte_t* data, size_t datasize)
{
	stream.write((char*)data, datasize);
}

void BinaryFileStreamWrapper::read(byte_t* dest, size_t count)
{
	stream.read((char*)dest, count);
}