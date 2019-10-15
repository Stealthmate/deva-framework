#include <DevaFramework/Scripting/Lua/LuaContext.hpp>
#include <DevaFramework\Util\Time.hpp>

#include <iostream>

using namespace DevaFramework;

template<uint64_t id>
class test {
public:
	virtual void f() {
		std::cout << "F " << id << std::endl;
	}
};

class TestDerive : public test<1>, public test<2> {
public:
	void test1() {
		test<1>::f();
	}
	void test2() {
		test<2>::f();
	}
};

int main() {
	/*LuaContext lua;
	lua.eval("print \"Hello me!\"");

	LOG.wtf("What");

	return 0;*/

	TestDerive td;
	td.test1();
	td.test2();
	
}