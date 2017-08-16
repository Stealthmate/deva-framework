#include "ByteBuffer.hpp"
#include <algorithm>

using namespace DevaFramework;

internal::ByteBufferViewer::ByteBufferViewer(std::shared_ptr<ByteBuffer> buffer) : mBuffer(buffer), mValid(true) {
	DevaFramework::registerObserver(*buffer, *this);
}

void internal::ByteBufferViewer::invalidate() {
	mValid = false;
}

void internal::ByteBufferViewer::destroy() {
	invalidate();
	mBuffer.reset();
}

ByteBuffer& internal::ByteBufferViewer::buffer() {
	if (!mValid) {
		throw DevaException("Buffer is no longer valid");
	}
	auto p = mBuffer.lock();

	return *p;
	
}

const ByteBuffer& internal::ByteBufferViewer::buffer() const {
	if (!mValid) {
		throw DevaException("Buffer is no longer valid");
	}
	auto p = mBuffer.lock();

	return *p;
}

internal::ByteBufferViewer::~ByteBufferViewer() {
	mValid = false;
}

ByteBuffer::ByteBuffer() : ByteBuffer(0) {}

ByteBuffer::ByteBuffer(size_t size) : ByteBuffer(std::make_unique<std::vector<byte_t>>(size)) {}

ByteBuffer::ByteBuffer(std::unique_ptr<std::vector<byte_t>> buffer) : buffer(std::move(buffer)) {}

ByteBuffer& ByteBuffer::operator=(ByteBuffer &&rhs) = default;

size_t ByteBuffer::size() const
{
	if (!buffer) return 0;
	return this->buffer->size();
}

bool ByteBuffer::isActive() const {
	return !!buffer;
}

void ByteBuffer::write(const byte_t* data, size_t count, size_t pos, size_t offset)
{
	if (!isActive()) {
		throw DevaException("Buffer has been released");
	}

	if (count + pos > buffer->size())
		throw DevaException
		("Attempted to write beyond buffer size. (" + strm(count + pos) + " > " + strm(buffer->size()) + ")");

	for (int i = 0;i <= count - 1;i++)
	{
		(*buffer)[pos + i] = data[offset + i];
	}
}

size_t ByteBuffer::read(byte_t* dest, size_t count, size_t pos, size_t offset) const
{
	if (!isActive()) {
		throw DevaException("Buffer has been released");
	}

	if (pos >= buffer->size())
		throw DevaInvalidArgumentException("Position " + strm(pos) + " larger than buffer size " + strm(buffer->size()));

	size_t i = 0;
	for (i = pos; i < std::min(pos + count, buffer->size()); i++)
	{
		dest[offset + i - pos] = (*buffer)[i];
	}

	return i - pos;

}

void ByteBuffer::resize(size_t new_size)
{
	if (!isActive()) {
		throw DevaException("Buffer has been released");
	}

	buffer->resize(new_size);

}

const std::vector<byte_t>& ByteBuffer::buf() const
{
	if (!isActive()) {
		throw DevaException("Buffer has been released");
	}

	return *buffer;
}

std::unique_ptr<std::vector<byte_t>> ByteBuffer::release() {
	return std::move(buffer);
}

ByteBuffer::~ByteBuffer() = default;