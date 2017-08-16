#ifndef DEVA_FRAMEWORK_GRAPHICS_VERTEX_BUFFER_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VERTEX_BUFFER_HPP

#include "Config.hpp"

#include "Model.hpp"

#include <vector>

namespace DevaFramework
{

	enum VertexBufferLayout {
		INTERLEAVED,
		SEPARATE
	};

	class VertexBuffer {

	public:

		DEVA_FRAMEWORK_API static VertexBuffer convertToLayout(const VertexBuffer &vertexData, VertexBufferLayout layout);

		struct Vertex {
			std::vector<byte_t*> elements;

			DEVA_FRAMEWORK_API Vertex() = default;
			DEVA_FRAMEWORK_API Vertex(const std::vector<byte_t*> &ptrs) : elements(ptrs) {}
		};

		class VertexBufferIterator {
			DEVA_FRAMEWORK_API VertexBufferIterator(VertexBuffer& vertexData, size_t index);

		public:
			DEVA_FRAMEWORK_API VertexBufferIterator operator++();
			DEVA_FRAMEWORK_API VertexBufferIterator operator--();
			DEVA_FRAMEWORK_API VertexBufferIterator operator+(size_t increment);
			DEVA_FRAMEWORK_API Vertex& operator*();
			DEVA_FRAMEWORK_API Vertex * operator->();

			DEVA_FRAMEWORK_API bool operator==(const VertexBufferIterator &iter) const;
			DEVA_FRAMEWORK_API bool operator!=(const VertexBufferIterator &iter) const;

		private:
			VertexBuffer& vertexData;
			size_t index;
			Vertex current;

			friend class VertexBuffer;
		};
		class VertexBufferIteratorConst {

			DEVA_FRAMEWORK_API VertexBufferIteratorConst(const VertexBuffer &vertexData, size_t index);

		public:
			DEVA_FRAMEWORK_API VertexBufferIteratorConst operator++();
			DEVA_FRAMEWORK_API VertexBufferIteratorConst operator--();
			DEVA_FRAMEWORK_API VertexBufferIteratorConst operator+(size_t increment);
			DEVA_FRAMEWORK_API const Vertex& operator*() const;
			DEVA_FRAMEWORK_API const Vertex * operator->() const;

			DEVA_FRAMEWORK_API bool operator==(const VertexBufferIteratorConst &iter) const;
			DEVA_FRAMEWORK_API bool operator!=(const VertexBufferIteratorConst &iter) const;

		private:
			const VertexBuffer& vertexData;
			size_t index;
			Vertex current;

			friend class VertexBuffer;
		};

		DEVA_FRAMEWORK_API VertexBuffer(
			std::unique_ptr<std::vector<byte_t>> vertexData, 
			size_t vertexCount, 
			const std::vector<VertexDataElementDescription> &mVertexElementDescriptions, 
			VertexBufferLayout layout);

		DEVA_FRAMEWORK_API VertexBufferIterator begin() { return VertexBufferIterator(*this, 0);  }
		DEVA_FRAMEWORK_API VertexBufferIteratorConst begin() const { return VertexBufferIteratorConst(*this, 0); }
		DEVA_FRAMEWORK_API VertexBufferIterator end() { return VertexBufferIterator(*this, mVertexCount); }
		DEVA_FRAMEWORK_API VertexBufferIteratorConst end() const { return VertexBufferIteratorConst(*this, mVertexCount); }

		DEVA_FRAMEWORK_API Vertex operator[](size_t index);
		DEVA_FRAMEWORK_API const Vertex operator[](size_t index) const;

		DEVA_FRAMEWORK_API const std::vector<byte_t>& vertexData() const { return *mVertexData;  }
		DEVA_FRAMEWORK_API std::unique_ptr<std::vector<byte_t>> release();

		DEVA_FRAMEWORK_API bool isActive() const;
		DEVA_FRAMEWORK_API size_t vertexCount() const { return mVertexCount; }
		DEVA_FRAMEWORK_API std::vector<VertexDataElementDescription> elements() const { return mVertexElementDescriptions; }
		DEVA_FRAMEWORK_API size_t vertexSize() const;
		DEVA_FRAMEWORK_API VertexBufferLayout layout() const { return mLayout;  }

	private:
		std::unique_ptr<std::vector<byte_t>> mVertexData;
		size_t mVertexCount;
		std::vector<VertexDataElementDescription> mVertexElementDescriptions;
		VertexBufferLayout mLayout;
	};
}

#endif //DEVA_FRAMEWORK_GRAPHICS_VERTEX_BUFFER_HPP