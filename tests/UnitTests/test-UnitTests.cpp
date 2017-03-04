#include <DevaFramework\Util\ByteBuffer.hpp>
#include <gtest\gtest.h>
using namespace DevaFramework;

float readWriteBuffer(float f)
{
	ByteBuffer buf(4);
	buf << f;
	buf.setPosition(0);
	float result;
	buf >> result;
	return result;
}

std::string readWriteBuffer(std::string str)
{
	ByteBuffer buf(1000);
	buf.write((byte_t*)str.data(), str.length());
	buf.setPosition(0);
	byte_t cbuf[10];
	memset(cbuf, 0, 10);
	buf.read(cbuf, 10);
	return std::string((char*)cbuf);
}

TEST(BufferFloat, ByteBuffer) 
{
	EXPECT_EQ (1.0, readWriteBuffer(1.0));
}
TEST(BufferString, ByteBuffer)
{
	EXPECT_EQ("test", readWriteBuffer("test"));
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}