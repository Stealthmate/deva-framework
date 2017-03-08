#include "Common.hpp"

#include <fstream>
#include <stdarg.h> 

using namespace DevaFramework;

std::string DevaFramework::readTextFile(const char* filepath)
{
	std::string text = "\0";
	std::ifstream input(filepath, std::ios::in);

	if (input.is_open())
	{
		std::string Line = "";
		while (getline(input, Line))
			text += "\n" + Line;
		input.close();
	}
	else {
		
		throw DevaInvalidArgumentException(strformat("Cannot open file {}", filepath));
	}
	return text;
}

ByteBuffer DevaFramework::readBinaryFile(const char* filepath)
{
	ByteBuffer buffer(0);
	std::ifstream input(filepath, std::ios::ate | std::ios::binary);

	if (input.is_open())
	{
		buffer.resize((size_t)input.tellg());
		input.seekg(0);
		input.read((char*)buffer.buf().data(), buffer.size());
		input.close();
	}
	else {
		throw DevaInvalidArgumentException("Cannot open file " + std::string(filepath));
	}
	return buffer;
}