#include <DevaFramework\Util\ByteBuffer.hpp>
#include <gtest\gtest.h>

using namespace DevaFramework;
using namespace std;

class BufferTester : public ::testing::Test {
protected:
	ByteBuffer buffer;
	BufferTester() : buffer(17) {}
};

TEST_F(BufferTester, testByteBuffer)
{
	size_t pos = 0;
	ASSERT_NO_THROW(buffer.write((int)4, 0));
	pos += sizeof(int);
	ASSERT_NO_THROW(buffer.write((double)4.0, pos));
	pos += sizeof(double);

	char longdata[10000];
	ASSERT_THROW(buffer.write((byte_t*)longdata, sizeof(longdata), pos), DevaException);
	char shortdata[] = "data";
	ASSERT_NO_THROW(buffer.write((byte_t*)shortdata, sizeof(shortdata), pos));
	pos += sizeof(shortdata) * sizeof(char);
	ASSERT_THROW(buffer.write((byte_t*)shortdata, 10000000, pos), DevaException);

	cout << "Writing works" << endl;

	pos = 0;
	int val;
	ASSERT_NO_THROW(buffer.read(&val, pos));
	ASSERT_EQ(val, 4);
	pos += sizeof(int);

	double vald;
	ASSERT_NO_THROW(buffer.read(&vald, pos));
	ASSERT_EQ(vald, 4.0);
	pos += sizeof(double);

	memset(shortdata, 0, 5);
	ASSERT_NO_THROW(buffer.read((byte_t*)shortdata, 5, pos));
	ASSERT_EQ(string(shortdata), "data");
	cout << "Reading works" << endl;
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}