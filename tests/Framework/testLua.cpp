#include <DevaFramework/Scripting/Lua/LuaContext.hpp>
#include <DevaFramework\Util\Time.hpp>

#include <iostream>
#include <sstream>
using namespace DevaFramework;
using namespace std;

#include<atomic>

atomic<bool> over(false);

void threadloop() {
	stringstream str;
	while (cin) {
		string s;
		cin >> s;
		str << s;
	}
	LOG << "Read:\n" << str.str() << LOG.endl;
	over.store(true);
}
#include <thread>
int main() {
	LuaContext lua;
	lua.eval("print \"Hello me!\"");
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	auto i = std::thread(threadloop);
	size_t t = 0;
	size_t cap = 10e7;
	while (!over.load()) {
		if (t > cap) {
			cout << cin.rdbuf()->in_avail() << endl;
			t = 0;
		}
		t++;
	}
	i.join();
	return 0;
}