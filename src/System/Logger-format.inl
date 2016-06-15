#include "Config.hpp"

namespace {

	

	char hexarr[] = {
		'0', '1', '2', '3', '4',
		'5', '6', '7', '8', '9',
		'A', 'B', 'C', 'D', 'F'
	};

	std::string hex(char byte)
	{
		unsigned char ub = static_cast<unsigned char>(byte);
		std::string sb = "0x";
		sb += hexarr[ub / 16];
		sb += hexarr[ub % 16];
		return  sb;
	}
}

