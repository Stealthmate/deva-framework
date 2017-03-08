#include "LuaException.hpp"

using namespace DevaFramework;

LuaException::LuaException(const LuaContext &context, const std::string &msg) : DevaException(msg) {

}