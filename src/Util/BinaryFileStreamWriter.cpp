#include "BinaryFileStreamWriter.hpp"

using namespace DevaFramework;

BinaryFileStreamWriter::BinaryFileStreamWriter(const std::string &path, std::ios_base::openmode openmode)
{
	this->output = std::ofstream(path, openmode | std::ofstream::binary);
}

void BinaryFileStreamWriter::close()
{
	this->output.close();
}