#include "NumberFormatter.hpp"

namespace
{

	using namespace DevaFramework;

	char hexarr[] = {
		'0', '1', '2', '3', '4',
		'5', '6', '7', '8', '9',
		'A', 'B', 'C', 'D', 'E', 'F'
	};

	char binarr[] = { 0, 1 };

	std::string byte_to_hex(byte_t b)
	{
		std::string bstr = "";
		bstr += hexarr[b / 16];
		bstr += hexarr[b % 16];
		return  bstr;
	}

	std::string byte_to_binary(byte_t b)
	{
		std::string binstr = "";
		binstr += ((b & 0b10000000) > 0) + '0';
		binstr += ((b & 0b01000000) > 0) + '0';
		binstr += ((b & 0b00100000) > 0) + '0';
		binstr += ((b & 0b00010000) > 0) + '0';
		binstr += ((b & 0b00001000) > 0) + '0';
		binstr += ((b & 0b00000100) > 0) + '0';
		binstr += ((b & 0b00000010) > 0) + '0';
		binstr += ((b & 0b00000001) > 0) + '0';
		return binstr;
	}

	template<typename T>
	std::string getHexStringRepr(T data)
	{
		byte_t* number = reinterpret_cast<byte_t*>(&data);
		std::string repr = "0x";
		for (int i = 0;i <= sizeof(T) - 1;i++)
		{
			repr += byte_to_hex(number[i]);
		}
		return  repr;
	}

	template<typename T>
	std::string getBinaryStringRepr(T data)
	{
		byte_t* number = reinterpret_cast<byte_t*>(&data);
		std::string repr = "0b";
		for (int i = 0;i <= sizeof(T) - 1;i++)
		{
			repr += byte_to_binary(number[i]) + " ";
		}
		return  repr;
	}

}

std::string NumberFormatter::toBinary(byte_t data) { return getBinaryStringRepr(data); }
std::string NumberFormatter::toBinary(int16_t data) { return getBinaryStringRepr(data); }
std::string NumberFormatter::toBinary(uint16_t data) { return getBinaryStringRepr(data); }
std::string NumberFormatter::toBinary(int32_t data) { return getBinaryStringRepr(data); }
std::string NumberFormatter::toBinary(uint32_t data) { return getBinaryStringRepr(data); }
std::string NumberFormatter::toBinary(int64_t data) { return getBinaryStringRepr(data); }
std::string NumberFormatter::toBinary(uint64_t data) { return getBinaryStringRepr(data); }

std::string NumberFormatter::toHex(byte_t data) { return getHexStringRepr(data);  }
std::string NumberFormatter::toHex(int16_t data) { return getHexStringRepr(data);  }
std::string NumberFormatter::toHex(uint16_t data) { return getHexStringRepr(data);  }
std::string NumberFormatter::toHex(int32_t data) { return getHexStringRepr(data);  }
std::string NumberFormatter::toHex(uint32_t data) { return getHexStringRepr(data);  }
std::string NumberFormatter::toHex(int64_t data) { return getHexStringRepr(data);  }
std::string NumberFormatter::toHex(uint64_t data) { return getHexStringRepr(data);  }