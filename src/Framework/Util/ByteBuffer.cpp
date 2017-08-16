#include "ByteBuffer.hpp"
#include <algorithm>

using namespace DevaFramework;

ByteBuffer::ByteBufferViewer::ByteBufferViewer(std::shared_ptr<ByteBuffer> buffer) : mBuffer(buffer), mValid(true) {
	buffer->subscribeViewer(this);

}

void ByteBuffer::ByteBufferViewer::invalidate() {
	mValid = false;
	mBuffer.reset();
}

ByteBuffer& ByteBuffer::ByteBufferViewer::buffer() {
	if (!mValid) {
		throw DevaException("Buffer is no longer valid");
	}
	auto p = mBuffer.lock();

	return *p;
	
}

const ByteBuffer& ByteBuffer::ByteBufferViewer::buffer() const {
	if (!mValid) {
		throw DevaException("Buffer is no longer valid");
	}
	auto p = mBuffer.lock();

	return *p;
}

ByteBuffer::ByteBufferViewer::~ByteBufferViewer() {
	mValid = false;
	auto ptr = mBuffer.lock();
	if (ptr)
		ptr->unsubscribeViewer(this);
	mBuffer.reset();
}

ByteBuffer::ByteBuffer() : ByteBuffer(0) {}

ByteBuffer::ByteBuffer(size_t size) : ByteBuffer(std::make_unique<std::vector<byte_t>>(size)) {}

ByteBuffer::ByteBuffer(std::unique_ptr<std::vector<byte_t>> buffer) : buffer(std::move(buffer)) {}

size_t ByteBuffer::size() const
{
	return this->buffer->size();
}

void ByteBuffer::write(const byte_t* data, size_t count, size_t pos, size_t offset)
{
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
	buffer->resize(new_size);
}

const std::vector<byte_t>& ByteBuffer::buf() const
{
	return *buffer;
}

void ByteBuffer::subscribeViewer(ByteBuffer::ByteBufferViewer *viewer) const {
	if (std::find(viewers.begin(), viewers.end(), viewer) == viewers.end()) {
		viewers.push_back(viewer);
	}
}

void ByteBuffer::unsubscribeViewer(ByteBuffer::ByteBufferViewer *viewer) const {
	
	auto el = std::find(viewers.begin(), viewers.end(), viewer);
	if(el != viewers.end()) {
		(*el)->invalidate();
		viewers.erase(el);
	}
}

ByteBuffer::~ByteBuffer() {
	for (auto v : viewers) {
		v->invalidate();
	}
}