#include <DevaFramework\Graphics\VertexBuffer.hpp>
#include <DevaFramework\Util\ByteBufferStream.hpp>
#include <gtest\gtest.h>

using namespace DevaFramework;
using namespace std;

class BufferTester : public ::testing::Test {
protected:
	VertexBuffer* buffer;
	BufferTester() : buffer() {}

	void SetUp() {

		auto bbuf = std::make_shared<ByteBuffer>(60);
		auto ostr = ByteBufferOutputStream(*bbuf);
		ostr << 1.f << 1.1f << 1.2f << 1.3f << 1.4f << 1.5f;
		ostr << 2.1f << 2.2f << 2.3f << 2.4f << 2.5f;
		ostr << 3.1f << 3.2f << 3.3f << 3.4f << 3.5f;
		vector<VertexDataElementDescription> elements;
		vector<size_t> components = { 32, 32, 32 };
		elements.push_back({ 3 * 4, FLOAT, components });
		components = { 32, 32 };
		elements.push_back({ 2 * 4, FLOAT, components });
		buffer = new VertexBuffer(bbuf->release(), 3, elements, INTERLEAVED);
	}

	~BufferTester()
	{
		delete buffer;
	}
};

TEST_F(BufferTester, testByteBuffer)
{
	EXPECT_EQ(buffer->vertexCount(), 3);
	EXPECT_EQ(buffer->vertexSize(), 20);
	EXPECT_EQ(buffer->layout(), INTERLEAVED);

	auto bbuf = std::make_shared<ByteBuffer>(60);
	auto ostr = ByteBufferOutputStream(*bbuf);
	ostr << 1.1f << 1.2f << 1.3f;
	ostr << 2.1f << 2.2f << 2.3f;
	ostr << 3.1f << 3.2f << 3.3f;
	ostr << 1.4f << 1.5f;
	ostr << 2.4f << 2.5f;
	ostr << 3.4f << 3.5f;
	//*bbuf.asWriteOnly().lock().setPosition(0);

	VertexBuffer vbremapped = VertexBuffer::convertToLayout(*buffer, SEPARATE);
	ByteBuffer remapped(std::move(vbremapped.release()));
	ByteBuffer init(std::move(buffer->release()));
	for (size_t i = 0;i < 9;i++)
	{
		float ref;
		bbuf->read(&ref, i * sizeof(float));
		float curr;
		remapped.read(&curr, i * sizeof(float));
		ASSERT_EQ(ref, curr);
	}

	cout << "Convert INTERLEAVED to SEPARATE works" << endl;
	remapped = VertexBuffer::convertToLayout(vbremapped, INTERLEAVED).release();
	for (size_t i = 0;i < 9;i++)
	{
		float ref;
		init.read(&ref, i * sizeof(float));
		float curr;
		remapped.read(&curr, i * sizeof(float));
		ASSERT_EQ(ref, curr);
	}

	cout << "Convert SEPARATE to INTERLEAVED works" << endl;
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}