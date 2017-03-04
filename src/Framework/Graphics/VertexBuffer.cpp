#include "VertexBuffer.hpp"

#include <numeric>

using namespace DevaFramework;

namespace {
	size_t sumComponentSizes(const std::vector<VertexDataElementDescription> &elements)
	{
		size_t sum = 0;
		for (auto & c : elements)
		{
			sum += c.size;
		}

		return sum;
	}
}

typedef VertexBuffer::VertexBufferIterator iterator;
typedef VertexBuffer::VertexBufferIteratorConst iteratorconst;
typedef VertexBuffer::Vertex vertex;


VertexBuffer VertexBuffer::convertToLayout(const VertexBuffer &buffer, VertexBufferLayout layout)
{
	std::vector<byte_t> data;
	data.resize(buffer.buffer().size());

	for (int i = 0;i < buffer.vertexCount();i++)
	{
		size_t offset = 0;
		for (int j = 0;j < buffer.elements().size();j++)
		{
			auto start = data.begin();
			switch (layout)
			{
			case INTERLEAVED:
			{
				start += (i * buffer.vertexSize()) + offset;
			}break;
			case SEPARATE:
			{
				start += (offset * buffer.vertexCount()) + (i*buffer.elements()[j].size);
			}break;
			}

			std::copy(buffer[i].elements[j], buffer[i].elements[j] + buffer.elements()[j].size, start);

			offset += buffer.elements()[j].size;
		}
	}

	return VertexBuffer(data, buffer.vertexCount(), buffer.elements(), layout);
}


//-------VertexBufferIterator-------//

iterator::VertexBufferIterator(VertexBuffer &buffer, size_t index) : buffer(buffer), index(index)
{
	if (index >= buffer.vertexCount()) current = Vertex();
	else current = buffer[index];
}

iterator iterator::operator++()
{
	iterator i = *this;

	i.index++;
	i.current = buffer[index];

	return i;
}

iterator iterator::operator+(size_t increment)
{
	iterator i = *this;

	i.index += increment;
	i.current = buffer[index];

	return i;
}

iterator iterator::operator--()
{
	iterator i = *this;

	i.index--;
	i.current = buffer[index];

	return i;
}

vertex& iterator::operator*()
{
	return current;
}

vertex* iterator::operator->()
{
	return &current;
}

bool iterator::operator==(const iterator &iter) const
{
	return &buffer == &iter.buffer && index == iter.index;
}

bool iterator::operator!=(const iterator &iter) const
{
	return !this->operator==(iter);
}

//------VertexBufferIteratorConst-------//

iteratorconst::VertexBufferIteratorConst(const VertexBuffer &buffer, size_t index) : buffer(buffer), index(index)
{
	if (index >= buffer.vertexCount()) current = Vertex();
	else current = buffer[index];
}


iteratorconst iteratorconst::operator++()
{
	iteratorconst i = *this;

	i.index++;
	i.current = buffer[index];

	return i;
}

iteratorconst iteratorconst::operator+(size_t increment)
{
	iteratorconst i = *this;

	i.index += increment;
	i.current = buffer[index];

	return i;
}

iteratorconst iteratorconst::operator--()
{
	iteratorconst i = *this;

	i.index--;
	i.current = buffer[index];

	return i;
}


const vertex& iteratorconst::operator*() const
{
	return current;
}

const vertex* iteratorconst::operator->() const
{
	return &current;
}

bool iteratorconst::operator==(const iteratorconst &iter) const
{
	return &buffer == &iter.buffer && index == iter.index;
}

bool iteratorconst::operator!=(const iteratorconst &iter) const
{
	return !this->operator==(iter);
}

//------VertexBuffer------//

vertex VertexBuffer::operator[](size_t index)
{
	std::vector<byte_t*> ptrs;
	ptrs.reserve(vertexSize());
	size_t comp_offset = 0;
	for (int i = 0;i < mElements.size();i++)
	{
		size_t start = 0;
		switch (mLayout)
		{
		case INTERLEAVED:
		{
			start += index * vertexSize();
		}break;
		case SEPARATE:
		{
			start += (comp_offset * mVertexCount) + index;
		}break;
		}

		ptrs.push_back(&mBuffer[start]);
	}

	return Vertex(ptrs);
}

const vertex VertexBuffer::operator[](size_t index) const
{
	std::vector<byte_t*> ptrs;
	ptrs.reserve(vertexSize());
	size_t comp_offset = 0;
	for (int i = 0;i < mElements.size();i++)
	{
		size_t start = 0;
		switch (mLayout)
		{
		case INTERLEAVED:
		{
			start += (index * vertexSize()) + comp_offset;
		}break;
		case SEPARATE:
		{
			start += (comp_offset * mVertexCount) + (index*mElements[i].size);
		}break;
		}

		ptrs.push_back(const_cast<byte_t*>(&mBuffer[start]));
		comp_offset += mElements[i].size;
	}

	return Vertex(ptrs);
}

VertexBuffer::VertexBuffer(
	const std::vector<byte_t> &data,
	size_t vertexCount,
	const std::vector<VertexDataElementDescription> &elements,
	VertexBufferLayout layout) : mBuffer(data), mVertexCount(vertexCount), mElements(elements), mLayout(layout) {}

size_t VertexBuffer::vertexSize() const
{
	return sumComponentSizes(mElements);
}
