#ifndef DEVA_FRAMEWORK_UTIL_COMMON_H
#define DEVA_FRAMEWORK_UTIL_COMMON_H 

#include "Config.hpp"
#include "ByteBuffer.hpp"

#include <string>
#include <vector>

namespace DevaFramework
{
	DEVA_FRAMEWORK_API std::string readTextFile(const char* filepath);
	DEVA_FRAMEWORK_API ByteBuffer readBinaryFile(const char* filepath);
	DEVA_FRAMEWORK_API std::vector<const char*> convertStringArrToPtrArr(const std::vector<std::string> &strings);
}

#endif //define DEVA_FRAMEWORK_UTIL_COMMON_H