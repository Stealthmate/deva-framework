#include "VertexBuffer.hpp"
#include "Mesh.hpp"

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


VertexBuffer VertexBuffer::convertToLayout(const VertexBuffer &vertexData, VertexBufferLayout layout)
{
	if (!vertexData.isDataValid()) {
		throw DevaException("Buffer has been released");
	}

	std::vector<byte_t> data(vertexData.vertexData().size());

	for (int i = 0;i < vertexData.vertexCount();i++)
	{
		size_t offset = 0;
		for (int j = 0;j < vertexData.elements().size();j++)
		{
			auto start = data.begin();
			switch (layout)
			{
			case INTERLEAVED:
			{
				start += (i * vertexData.vertexSize()) + offset;
			}break;
			case SEPARATE:
			{
				start += (offset * vertexData.vertexCount()) + (i*vertexData.elements()[j].size);
			}break;
			}

			std::copy(vertexData[i].elements[j], vertexData[i].elements[j] + vertexData.elements()[j].size, start);

			offset += vertexData.elements()[j].size;
		}
	}

	return VertexBuffer(std::move(data), vertexData.vertexCount(), vertexData.elements(), layout);
}


//-------VertexBufferIterator-------//

iterator::VertexBufferIterator(VertexBuffer &vertexData, size_t index) : vertexData(vertexData), index(index)
{
	if (index >= vertexData.vertexCount()) current = Vertex();
	else current = vertexData[index];
}

iterator iterator::operator++()
{
	iterator i = *this;

	i.index++;
	i.current = vertexData[index];

	return i;
}

iterator iterator::operator+(size_t increment)
{
	iterator i = *this;

	i.index += increment;
	i.current = vertexData[index];

	return i;
}

iterator iterator::operator--()
{
	iterator i = *this;

	i.index--;
	i.current = vertexData[index];

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
	return &vertexData == &iter.vertexData && index == iter.index;
}

bool iterator::operator!=(const iterator &iter) const
{
	return !this->operator==(iter);
}

//------VertexBufferIteratorConst-------//

iteratorconst::VertexBufferIteratorConst(const VertexBuffer &vertexData, size_t index) : vertexData(vertexData), index(index)
{
	if (index >= vertexData.vertexCount()) current = Vertex();
	else current = vertexData[index];
}


iteratorconst iteratorconst::operator++()
{
	iteratorconst i = *this;

	i.index++;
	i.current = vertexData[index];

	return i;
}

iteratorconst iteratorconst::operator+(size_t increment)
{
	iteratorconst i = *this;

	i.index += increment;
	i.current = vertexData[index];

	return i;
}

iteratorconst iteratorconst::operator--()
{
	iteratorconst i = *this;

	i.index--;
	i.current = vertexData[index];

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
	return &vertexData == &iter.vertexData && index == iter.index;
}

bool iteratorconst::operator!=(const iteratorconst &iter) const
{
	return !this->operator==(iter);
}

//------VertexBuffer------//

vertex VertexBuffer::operator[](size_t index)
{
	if (!isDataValid()) {
		throw DevaException("Buffer has been released");
	}

	std::vector<byte_t*> ptrs;
	ptrs.reserve(vertexSize());
	size_t comp_offset = 0;
	for (int i = 0;i < mVertexElementDescriptions.size();i++)
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

		ptrs.push_back(&mVertexData[start]);
	}

	return Vertex(ptrs);
}

const vertex VertexBuffer::operator[](size_t index) const
{
	if (!isDataValid()) {
		throw DevaException("Buffer has been released");
	}

	std::vector<byte_t*> ptrs;
	ptrs.reserve(vertexSize());
	size_t comp_offset = 0;
	for (int i = 0;i < mVertexElementDescriptions.size();i++)
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
			start += (comp_offset * mVertexCount) + (index*mVertexElementDescriptions[i].size);
		}break;
		}

		ptrs.push_back(const_cast<byte_t*>(&mVertexData[start]));
		comp_offset += mVertexElementDescriptions[i].size;
	}

	return Vertex(ptrs);
}

VertexBuffer::VertexBuffer(
	std::vector<byte_t>&& data,
	size_t vertexCount,
	const std::vector<VertexDataElementDescription> &elements,
	VertexBufferLayout layout) : mVertexData(std::move(data)), mVertexCount(vertexCount), mVertexElementDescriptions(elements), mLayout(layout) {}

size_t VertexBuffer::vertexSize() const
{
	if (!isDataValid()) {
		throw DevaException("Buffer has been released");
	}

	return sumComponentSizes(mVertexElementDescriptions);
}

std::vector<byte_t> VertexBuffer::onRelease() {
	return std::move(mVertexData);
}