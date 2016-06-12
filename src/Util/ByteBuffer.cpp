#include "ByteBuffer.hpp"

#include "../System/Exceptions.hpp"

using namespace DevaFramework;

ByteBuffer::ByteBuffer(size_t size) : buffer(size), position(0) {}

ByteBuffer::ByteBuffer(std::vector<char> &&buffer) : buffer(buffer), position(0) {}

void ByteBuffer::setPosition(size_t new_pos)
{
	if (new_pos > buffer.size() - 1) 
		throw DevaInvalidInputException
		("Attempted to set buffer position beyond buffer size. (" + strm(new_pos) +  " >= " + strm(buffer.size()) + ")");

	this->position = new_pos;
}

size_t ByteBuffer::getPosition() const
{
	return this->position;
}

ByteBuffer& ByteBuffer::write(const char* data, size_t count)
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

ByteBuffer& ByteBuffer::read(char* dest, size_t count)
{
	if (count + position > buffer.size() - 1)
		throw DevaInvalidInputException
		("Attempted to read beyond buffer size. (" + strm(count + position) + " >= " + strm(buffer.size()) + ")");

	for (int i = 0;i <= count - 1;i++)
	{
		dest[i] = buffer[position + i];
	}

	position += count;

	return *this;
}

const std::vector<char>& ByteBuffer::getBuffer() const
{
	return buffer;
}