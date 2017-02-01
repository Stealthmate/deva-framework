#include "ByteBuffer.hpp"

#include "../Exceptions.hpp"

using namespace DevaFramework;

ByteBuffer::ByteBuffer(size_t size) : buffer(size), position(0) {}

ByteBuffer::ByteBuffer(const std::vector<byte_t> &buffer) : buffer(buffer), position(0) {}

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

size_t ByteBuffer::size() const
{
	return this->buffer.size();
}

void ByteBuffer::write(const byte_t* data, size_t count)
{
	if (count + position > buffer.size())
		throw DevaException
		("Attempted to write beyond buffer size. (" + strm(count + position) + " > " + strm(buffer.size()) + ")");

	for (int i = 0;i <= count - 1;i++)
	{
		buffer[position + i] = data[i];
	}

	position += count;
}

void ByteBuffer::read(byte_t* dest, size_t count)
{
	if (count + position > buffer.size())
		throw DevaException
		("Attempted to read beyond buffer size. (" + strm(count + position) + " > " + strm(buffer.size()) + ")");

	for (int i = 0;i <= count - 1;i++)
	{
		dest[i] = buffer[position + i];
	}

	position += count;
}

void ByteBuffer::resize(size_t new_size)
{
	buffer.resize(new_size);
}

const std::vector<byte_t>& ByteBuffer::buf() const
{
	return buffer;
}
std::vector<byte_t>& ByteBuffer::buf()
{
	return buffer;
}