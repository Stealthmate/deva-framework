#include "ByteBufferStream.hpp"
#include <algorithm>

using namespace DevaFramework;

template <typename Type>
using sptr = std::shared_ptr<Type>;

internal::ByteBufferStreamBase::ByteBufferStreamBase(sptr<ByteBuffer> buffer) : ByteBufferViewer(buffer), position(0) {}
internal::ByteBufferStreamBase::~ByteBufferStreamBase() = default;

void internal::ByteBufferStreamBase::setPosition(size_t pos) {
	position = pos;
}

size_t internal::ByteBufferStreamBase::getPosition() const {
	return position;
}

void internal::ByteBufferStreamBase::revalidate() {
	position = 0;
}

ByteBufferInputStream::ByteBufferInputStream(sptr<ByteBuffer> buffer) : ByteBufferStreamBase(buffer) {}
ByteBufferInputStream::~ByteBufferInputStream() = default;

size_t ByteBufferInputStream::read(byte_t* dest, size_t count, size_t offset) {
	
	auto &buf = buffer();
	size_t bytes = std::min(count, buf.size() - position);

	buf.read(dest, bytes, position, offset);

	position += bytes;

	return bytes;
}

size_t ByteBufferInputStream::available() const {
	return buffer().size();
}

ByteBufferOutputStream::ByteBufferOutputStream(sptr<ByteBuffer> buffer) : ByteBufferStreamBase(buffer) {}
ByteBufferOutputStream::~ByteBufferOutputStream() = default;

void ByteBufferOutputStream::write(const byte_t* data, size_t count, size_t offset) {
	auto &buf = buffer();
	size_t bytes = std::min(count, buf.size() - position);

	buf.write(data, bytes, position, offset);

	position += bytes;
}