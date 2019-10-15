#ifndef DEVA_FRAMEWORK_UTIL_TYPE_INFO_HPP
#define DEVA_FRAMEWORK_UTIL_TYPE_INFO_HPP

#include "Config.hpp"

namespace DevaFramework {
	
	template<typename T> struct TypeInfo;

#define DEVA_REGISTER_TYPEINFO(type) \
	template<> struct TypeInfo<type> { static const std::string name; }; \
	const std::string TypeInfo<type>::name = #type; \

	DEVA_REGISTER_TYPEINFO(char);
	DEVA_REGISTER_TYPEINFO(signed char);
	DEVA_REGISTER_TYPEINFO(unsigned char);
	DEVA_REGISTER_TYPEINFO(short);
	DEVA_REGISTER_TYPEINFO(unsigned short);
	DEVA_REGISTER_TYPEINFO(int);
	DEVA_REGISTER_TYPEINFO(unsigned int);
	DEVA_REGISTER_TYPEINFO(long long);
	DEVA_REGISTER_TYPEINFO(unsigned long long);
}

#endif // DEVA_FRAMEWORK_UTIL_TYPE_INFO_HPP