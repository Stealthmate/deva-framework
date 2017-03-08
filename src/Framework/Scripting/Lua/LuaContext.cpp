#include "LuaContext.hpp"

#include "LuaException.hpp"

using namespace DevaFramework;

LuaContext::LuaContext() {
	mState = luaL_newstate();
	luaopen_base(mState);
}

LuaContext::LuaContext(LuaContext &&context) {
	mState = context.mState;
	context.mState = nullptr;
}

LuaContext& LuaContext::operator=(LuaContext &&context) {
	mState = context.mState;
	context.mState = nullptr;

	return *this;
}

LuaContext::~LuaContext() {
	if (mState)
		lua_close(mState);
}

void LuaContext::eval(const std::string &line) {
	int status = luaL_dostring(this->mState, line.c_str());
	if (status) {
		LOG_LUA.e("Execution failed for line:\n\t" + line);
	}
}

void LuaContext::defineFunction(LuaFunction f, const std::string &name) {
	if (customFunctions.find(name) != customFunctions.end()) {
		throw LuaException(*this, "Function with name " + name + " already exists.");
	}
	lua_register(mState, name.c_str(), f);
}