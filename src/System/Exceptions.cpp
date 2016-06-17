#include "Exceptions.hpp"

#include "DevaLogger.hpp"

using namespace DevaFramework;

namespace
{
	const std::string DEVA_EXCEPTION = "DevaException:";
}

DevaException::DevaException() : stamp(DEVA_EXCEPTION) {}

DevaException::DevaException(const std::string &description) 
	: stamp(DEVA_EXCEPTION), description(description), full_description(stamp + ": " + description) {}

DevaException::DevaException(const std::string &stamp, const std::string &description, const std::string &full_description) 
	: stamp(stamp), description(description), full_description(full_description) {}

const char* DevaException::what() const
{
	return this->full_description.c_str();
}