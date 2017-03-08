#ifndef DEVA_FRAMEWORK_SCRIPTING_LUA_LUA_EXCEPTION_HPP
#define DEVA_FRAMEWORK_SCRIPTING_LUA_LUA_EXCEPTION_HPP

#include "Config.hpp"

#include "LuaContext.hpp"

namespace DevaFramework {
	class LuaException : public DevaException {
	public:
		DEVA_FRAMEWORK_API LuaException(const LuaContext &context, const std::string &msg);
	};
}

#endif // DEVA_FRAMEWORK_SCRIPTING_LUA_LUA_EXCEPTION_HPP