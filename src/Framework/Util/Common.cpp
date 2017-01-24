#include "Common.hpp"

#include "../Exceptions.hpp"

#include <fstream>

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
		throw DevaInvalidArgumentException("Cannot open file " + strm(filepath));
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
		input.read(buffer.buf().data(), buffer.size());
		input.close();
	}
	else {
		throw DevaInvalidArgumentException("Cannot open file " + strm(filepath));
	}
	return buffer;
}