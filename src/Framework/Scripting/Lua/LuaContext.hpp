#ifndef DEVA_FRAMEWORK_SCRIPTING_LUA_LUA_CONTEXT_HPP
#define DEVA_FRAMEWORK_SCRIPTING_LUA_LUA_CONTEXT_HPP

#include "Config.hpp"

#include <unordered_map>

#include <lua\lua.hpp>

namespace DevaFramework {

	typedef lua_CFunction LuaFunction;

	class LuaContext {
		lua_State * mState;
		std::unordered_map<std::string, LuaFunction> customFunctions;


		LuaContext(const LuaContext &context) = delete;
		LuaContext& operator=(const LuaContext &context) = delete;

	public:
		DEVA_FRAMEWORK_API LuaContext();
		DEVA_FRAMEWORK_API LuaContext(LuaContext &&context);
		DEVA_FRAMEWORK_API LuaContext& operator=(LuaContext &&context);
		DEVA_FRAMEWORK_API ~LuaContext();

		DEVA_FRAMEWORK_API void eval(const std::string &line);
		DEVA_FRAMEWORK_API void defineFunction(LuaFunction f, const std::string &name);

		DEVA_FRAMEWORK_API std::unordered_map<std::string, LuaFunction> getCustomFunctions() const;
	};
}

#endif // DEVA_FRAMEWORK_SCRIPTING_LUA_LUA_CONTEXT_HPP