#include "DevaException.hpp"

using namespace DevaFramework;

namespace
{
	const std::string DEVA_EXCEPTION = "DevaException:";
}

DevaException::DevaException(const std::string &description)
	: stamp(DEVA_EXCEPTION), description(description)
{
	full_description = stamp + " " + description;
}

const char* DevaException::what() const
{
	return this->full_description.c_str();
}

std::string DevaFramework::DevaException::getStamp() const
{
	return this->stamp;
}
