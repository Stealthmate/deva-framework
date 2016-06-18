#ifndef DEVA_FRAMEWORK_SYSTEM_NUMBER_FORMATTER_H
#define DEVA_FRAMEWORK_SYSTEM_NUMBER_FORMATTER_H

#include "Config.hpp"

namespace DevaFramework
{
	struct NumberFormatter
	{
		DEVA_FRAMEWORK_API static std::string toBinary(byte_t data);
		DEVA_FRAMEWORK_API static std::string toBinary(int16_t data);
		DEVA_FRAMEWORK_API static std::string toBinary(uint16_t data);
		DEVA_FRAMEWORK_API static std::string toBinary(int32_t data);
		DEVA_FRAMEWORK_API static std::string toBinary(uint32_t data);
		DEVA_FRAMEWORK_API static std::string toBinary(int64_t data);
		DEVA_FRAMEWORK_API static std::string toBinary(uint64_t data);

		DEVA_FRAMEWORK_API static std::string toHex(byte_t data);
		DEVA_FRAMEWORK_API static std::string toHex(int16_t data);
		DEVA_FRAMEWORK_API static std::string toHex(uint16_t data);
		DEVA_FRAMEWORK_API static std::string toHex(int32_t data);
		DEVA_FRAMEWORK_API static std::string toHex(uint32_t data);
		DEVA_FRAMEWORK_API static std::string toHex(int64_t data);
		DEVA_FRAMEWORK_API static std::string toHex(uint64_t data);
	};
}

#endif // DEVA_FRAMEWORK_SYSTEM_NUMBER_FORMATTER_h