#include <DevaFramework/Scripting/Lua/LuaContext.hpp>

#include <iostream>

using namespace DevaFramework;

int main() {
	LuaContext lua;
	lua.eval("print \"Hello me!\"");

	LOG.wtf("What");

	return 0;
}