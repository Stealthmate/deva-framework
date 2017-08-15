#include "ByteBuffer.hpp"
#include <algorithm>

using namespace DevaFramework;

using namespace DevaFramework::internal;

class internal::ByteBufferView {

public:

	void invalidate() {
		valid = false;
	}

	ByteBufferView(ByteBuffer &buffer, size_t start) : buffer(buffer), START(start) {}

protected:
	ByteBuffer& buffer;

	const size_t START;
private:
	mutable bool valid;
};

class ByteBufferReader : public ByteBufferView, public ByteInputStream {
public:

	size_t read(byte_t * dest, size_t count, size_t offset) override {
		auto bytes = buffer.readAtPos(dest, std::min(count, END - position - START), START + position, offset);
		position += bytes;
		return bytes;
	}

	size_t available() const override {
		return END - START - position;
	}

	ByteBufferReader(const ByteBuffer &buffer, size_t start, size_t end) 
		: ByteBufferView(const_cast<ByteBuffer&>(buffer), start), END(end), position(0) {}

private:

	const size_t END;
	size_t position;

};

class ByteBufferWriter : public ByteBufferView, public ByteOutputStream {
public:

	void write(const byte_t* data, size_t count, size_t offset = 0) override {

		if (START + position + count > end) {
			if (autoexpand) {
				end = START + position + count;
				if (end >= buffer.size())
					buffer.resize(end);
			}
			else {
				throw DevaInvalidArgumentException("Attempt to overflow nonexpanding buffer");
			}
		}

		buffer.write(data, count, offset);
	}

	ByteBufferWriter(ByteBuffer &buffer, size_t start, size_t end, bool autoexpand) 
		: ByteBufferView(buffer, start), end(end), autoexpand(autoexpand), position(0) {}

private:
	size_t position;
	bool autoexpand;
	size_t end;
};

ByteBuffer::ByteBuffer() : ByteBuffer(0) {}

ByteBuffer::ByteBuffer(size_t size) : ByteBuffer(std::vector<byte_t>(size)) {}

ByteBuffer::ByteBuffer(const std::vector<byte_t> &buffer) : buffer(buffer), position(0) {}

void ByteBuffer::setPosition(size_t new_pos)
{
	if (new_pos > buffer.size() - 1)
		throw DevaInvalidInputException
		("Attempted to set buffer position beyond buffer size. (" + strm(new_pos) + " >= " + strm(buffer.size()) + ")");

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

void ByteBuffer::write(const byte_t* data, size_t count, size_t offset)
{
	if (count + position > buffer.size())
		throw DevaException
		("Attempted to write beyond buffer size. (" + strm(count + position) + " > " + strm(buffer.size()) + ")");

	for (int i = 0;i <= count - 1;i++)
	{
		buffer[position + i] = data[offset + i];
	}

	position += count;
}

size_t ByteBuffer::read(byte_t* dest, size_t count, size_t offset)
{
	if (count + position > buffer.size())
		throw DevaException
		("Attempted to read beyond buffer size. (" + strm(count + position) + " > " + strm(buffer.size()) + ")");

	size_t i;
	for (i = position;i < std::min(count, buffer.size() - position);i++)
	{
		dest[i] = buffer[position + i];
	}

	position += i;

	return i;
}

size_t ByteBuffer::readAtPos(byte_t* dest, size_t count, size_t pos, size_t offset) const
{
	if (pos >= buffer.size())
		throw DevaInvalidArgumentException("Position " + strm(pos) + " larger than buffer size " + strm(buffer.size()));

	size_t i = 0;
	for (i = pos; i < std::min(pos + count, buffer.size()); i++)
	{
		dest[offset + i - pos] = buffer[i];
	}

	return i - pos;

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

std::weak_ptr<ByteInputStream> ByteBuffer::asReadOnly(size_t start, size_t end) const {
	auto ptr = std::make_shared<ByteBufferReader>(*this, start, end);
	viewers.push_back(std::static_pointer_cast<internal::ByteBufferView>(ptr));
	return std::static_pointer_cast<ByteInputStream>(ptr);
}

std::weak_ptr<ByteOutputStream> ByteBuffer::asWriteOnly(size_t start, size_t end, bool autoexpand) {
	auto ptr = std::make_shared<ByteBufferWriter>(*this, start, end, autoexpand);
	viewers.push_back(std::static_pointer_cast<internal::ByteBufferView>(ptr));
	return std::static_pointer_cast<ByteOutputStream>(ptr);
}

ByteBuffer::~ByteBuffer() {
	for (auto v : viewers) {
		v->invalidate();
	}
}