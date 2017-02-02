#include <DevaFramework\Graphics\VertexBuffer.hpp>
#include <DevaFramework\Util\ByteBuffer.hpp>
#include <DevaFramework\Exceptions.hpp>
#include <gtest\gtest.h>

using namespace DevaFramework;
using namespace std;

class BufferTester : public ::testing::Test {
protected:
	VertexBuffer* buffer;
	BufferTester() : buffer() {}

	void SetUp() {

		ByteBuffer bbuf(36);
		bbuf << 1.1f << 1.2f << 1.3f;
		bbuf << 2.1f << 2.2f << 2.3f;
		bbuf << 3.1f << 3.2f << 3.3f;

		vector<VertexComponentInfo> components;
		components.push_back({ 4, FLOAT });
		components.push_back({ 4, FLOAT });
		components.push_back({ 4, FLOAT });

		buffer = new VertexBuffer(bbuf.buf(), 3, components, INTERLEAVED);
	}

	~BufferTester()
	{
		delete buffer;
	}
};

TEST_F(BufferTester, testByteBuffer)
{
	EXPECT_EQ(buffer->vertexCount(), 3);
	EXPECT_EQ(buffer->vertexSize(), 12);
	EXPECT_EQ(buffer->layout(), INTERLEAVED);

	ByteBuffer bbuf(36);
	bbuf << 1.1f << 2.1f << 3.1f;
	bbuf << 1.2f << 2.2f << 3.2f;
	bbuf << 1.3f << 2.3f << 3.3f;
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