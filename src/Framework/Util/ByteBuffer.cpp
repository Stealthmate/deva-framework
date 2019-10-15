#include "ByteBuffer.hpp"
#include <algorithm>

using namespace DevaFramework;

class internal::ByteBufferMessage {

public:

	enum EventType {
		BUFFER_RESIZED
	};

	ByteBufferMessage(EventType evttype) : evttype(evttype) {}


	const EventType evttype;
};

using internal::ByteBufferMessage;
using internal::ByteBufferViewer;

ByteBufferViewer::ByteBufferViewer(ByteBuffer &buffer) : mBuffer(buffer), mValid(true) {
	DevaFramework::registerObserver(buffer, *this);
}

void ByteBufferViewer::invalidate() {
	mValid = false;
}

void ByteBufferViewer::onNotify(ObservedObject& buf, const ByteBufferMessage &msg) {
	invalidate();
}

void ByteBufferViewer::onObservableDestroy(Observable<ByteBufferMessage> *o) {
	invalidate();
}

ByteBuffer& ByteBufferViewer::buffer() {
	if (!mValid) {
		throw DevaException("Buffer is no longer valid");
	}
	return mBuffer;
	
}

const ByteBuffer& ByteBufferViewer::buffer() const {
	if (!mValid) {
		throw DevaException("Buffer is no longer valid");
	}
	return mBuffer;
}

ByteBufferViewer::~ByteBufferViewer() {
	mValid = false;
}

ByteBuffer::ByteBuffer() : ByteBuffer(0) {}

ByteBuffer::ByteBuffer(size_t size) : buffer(size) {}

ByteBuffer::ByteBuffer(std::vector<byte_t> buffer) : buffer(std::move(buffer)) {}

ByteBuffer::ByteBuffer(const ByteBuffer &buffer) = default;
ByteBuffer& ByteBuffer::operator=(const ByteBuffer &rhs) = default;
ByteBuffer::ByteBuffer(ByteBuffer &&buffer) = default;
ByteBuffer& ByteBuffer::operator=(ByteBuffer &&rhs) = default;

size_t ByteBuffer::size() const
{
	if (!isDataValid()) return 0;
	return buffer.size();
}

void ByteBuffer::write(const byte_t* data, size_t count, size_t pos, size_t offset)
{
	if (!isDataValid()) {
		throw DevaException("Buffer has been released");
	}

	if (count + pos > buffer.size())
		throw DevaException
		("Attempted to write beyond buffer size. (" + strf(count + pos) + " > " + strf(buffer.size()) + ")");

	for (int i = 0;i <= count - 1;i++)
	{
		buffer[pos + i] = data[offset + i];
	}
}

size_t ByteBuffer::read(byte_t* dest, size_t count, size_t pos, size_t offset) const
{
	if (!isDataValid()) {
		throw DevaException("Buffer has been released");
	}

	if (pos >= buffer.size())
		throw DevaInvalidArgumentException("Position " + strf(pos) + " larger than buffer size " + strf(buffer.size()));

	size_t i = 0;
	for (i = pos; i < std::min(pos + count, buffer.size()); i++)
	{
		dest[offset + i - pos] = buffer[i];
	}

	return i - pos;

}

void ByteBuffer::resize(size_t new_size)
{
	if (!isDataValid()) {
		throw DevaException("Buffer has been released");
	}

	buffer.resize(new_size);
	notifyObservers({ByteBufferMessage::EventType::BUFFER_RESIZED});

}

const std::vector<byte_t>& ByteBuffer::buf() const
{
	if (!isDataValid()) {
		throw DevaException("Buffer has been released");
	}

	return buffer;
}

std::vector<byte_t> ByteBuffer::onRelease() {
	return std::move(buffer);
}

ByteBuffer::~ByteBuffer() = default;