#include <DevaFramework\Util\MultiTypeVector.hpp>
#include <iostream>
#include <DevaFramework\Core\Serializable.hpp>
#include <DevaFramework\Core\Exceptions.hpp>


#include <gtest\gtest.h>

using namespace std;
using namespace DevaFramework;

class Tester : public ::testing::Test {
protected:
	PackedVector<int, double> vec;
	Tester() : vec() {}
};

TEST_F(Tester, testWriteRead) {

	PackedVector<int, double> packv;
	ASSERT_NO_THROW(packv.push_back({ 1, 2.2 }));
	ASSERT_NO_THROW(packv.push_back({ 2, 2.3 }));
	Pack<int, double> p = { 0, 0.0 };

	cout << "Insertion works\n";

	ASSERT_NO_THROW(p = packv[0]);
	ASSERT_EQ(std::get<0>(p), 1);
	ASSERT_EQ(std::get<1>(p), 2.2);

	cout << "Extract 0 works\n";

	ASSERT_NO_THROW(p = packv[1]);
	ASSERT_EQ(std::get<0>(p), 2);
	ASSERT_EQ(std::get<1>(p), 2.3);

	cout << "Extract 1 works\n";
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}