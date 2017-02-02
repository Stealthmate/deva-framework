#include <DevaFramework\Util\ByteBuffer.hpp>
#include <DevaFramework\Exceptions.hpp>
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
	ASSERT_NO_THROW(buffer << 4);
	ASSERT_NO_THROW(buffer << 4.0);

	char longdata[10000];
	ASSERT_THROW(buffer.write((byte_t*)longdata, sizeof(longdata)), DevaException);
	char shortdata[] = "data";
	ASSERT_NO_THROW(buffer.write((byte_t*)shortdata, sizeof(shortdata)));
	ASSERT_THROW(buffer.write((byte_t*)shortdata, 10000000), DevaException);

	cout << "Writing works" << endl;

	ASSERT_NO_THROW(buffer.setPosition(10));
	ASSERT_THROW(buffer.setPosition(100000), DevaException);

	ASSERT_EQ(10, buffer.getPosition());
	ASSERT_NO_THROW(buffer.setPosition(0));

	cout << "setPosition works" << endl;

	int val;
	ASSERT_NO_THROW(buffer.read(reinterpret_cast<byte_t*>(&val), 4));
	ASSERT_EQ(val, 4);

	double vald;
	ASSERT_NO_THROW(buffer.read(reinterpret_cast<byte_t*>(&vald), sizeof(double)));
	ASSERT_EQ(vald, 4.0);

	memset(shortdata, 0, 5);
	ASSERT_NO_THROW(buffer.read((byte_t*)shortdata, 5));
	ASSERT_EQ(string(shortdata), "data");
	cout << "Reading works" << endl;
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}