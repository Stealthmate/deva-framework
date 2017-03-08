#include <DevaFramework\Graphics\VertexBuffer.hpp>
#include <DevaFramework\Util\ByteBuffer.hpp>
#include <gtest\gtest.h>

using namespace DevaFramework;
using namespace std;

class BufferTester : public ::testing::Test {
protected:
	VertexBuffer* buffer;
	BufferTester() : buffer() {}

	void SetUp() {

		ByteBuffer bbuf(60);
		bbuf << 1.1f << 1.2f << 1.3f << 1.4f << 1.5f;
		bbuf << 2.1f << 2.2f << 2.3f << 2.4f << 2.5f;
		bbuf << 3.1f << 3.2f << 3.3f << 3.4f << 3.5f;
		vector<VertexDataElementDescription> elements;
		vector<size_t> components = { 32, 32, 32 };
		elements.push_back({ 3 * 4, FLOAT, components });
		components = { 32, 32 };
		elements.push_back({ 2 * 4, FLOAT, components });
		buffer = new VertexBuffer(bbuf.buf(), 3, elements, INTERLEAVED);
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

	ByteBuffer bbuf(60);
	bbuf << 1.1f << 1.2f << 1.3f;
	bbuf << 2.1f << 2.2f << 2.3f;
	bbuf << 3.1f << 3.2f << 3.3f;
	bbuf << 1.4f << 1.5f;
	bbuf << 2.4f << 2.5f;
	bbuf << 3.4f << 3.5f;
	bbuf.setPosition(0);

	VertexBuffer vbremapped = VertexBuffer::convertToLayout(*buffer, SEPARATE);
	ByteBuffer remapped = ByteBuffer(vbremapped.buffer());
	ByteBuffer init = ByteBuffer(buffer->buffer());
	for (size_t i = 0;i < 9;i++)
	{
		float ref;
		bbuf >> ref;
		float curr;
		remapped >> curr;
		ASSERT_EQ(ref, curr);
	}

	cout << "Convert INTERLEAVED to SEPARATE works" << endl;
	remapped = VertexBuffer::convertToLayout(vbremapped, INTERLEAVED).buffer();
	for (size_t i = 0;i < 9;i++)
	{
		float ref;
		init >> ref;
		float curr;
		remapped >> curr;
		ASSERT_EQ(ref, curr);
	}

	cout << "Convert SEPARATE to INTERLEAVED works" << endl;
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}