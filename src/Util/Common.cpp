#include "Common.hpp"

#include <fstream>

std::string DevaFramework::readTextFile(const char* filepath)
{
	std::string text = "\0";
	std::ifstream input(filepath, std::ios::in);

	if (input.is_open())
	{
		std::string Line = "";
		while (getline(input, Line))
			text += "\n" + Line;
		input.close();
	}
	return text;
}