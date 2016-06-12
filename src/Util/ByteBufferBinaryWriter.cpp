#include "ByteBufferBinaryWriter.hpp"

#include "../System/Exceptions.hpp"

using namespace DevaFramework;

ByteBufferBinaryWriter::ByteBufferBinaryWriter(size_t size) : buffer(size), position(0) {}

ByteBufferBinaryWriter::ByteBufferBinaryWriter(std::vector<char> &&buffer) : buffer(buffer), position(0) {}

void ByteBufferBinaryWriter::setPosition(size_t new_pos)
{
	if (new_pos > buffer.size() - 1) 
		throw DevaInvalidInputException
		("Attempted to set buffer position beyond buffer size. (" + strm(new_pos) +  " >= " + strm(buffer.size()) + ")");

	this->position = new_pos;
}

size_t ByteBufferBinaryWriter::getPosition() const
{
	return this->position;
}

ByteBufferBinaryWriter& ByteBufferBinaryWriter::write(const char* data, size_t count)
{
	if (count + position > buffer.size() - 1)
		throw DevaInvalidInputException
		("Attempted to write beyond buffer size. (" + strm(count + position) + " >= " + strm(buffer.size()) + ")");

	for (int i = 0;i <= count - 1;i++)
	{
		buffer[position + i] = data[i];
	}

	position += count;

	return *this;
}

const std::vector<char>& ByteBufferBinaryWriter::getBuffer() const
{
	return buffer;
}