#include "Exceptions.hpp"

using namespace DevaFramework;

DevaException::DevaException()
{
	this->description = this->getStamp();
}

DevaException::DevaException(const std::string &description) 
{
	this->description = this->getStamp() + description;
}

const std::string DevaException::getStamp() const
{
	return "DevaException: ";
}

const char* DevaException::what() const
{
	return this->description.c_str();
}

const std::string DevaInvalidInputException::getStamp() const
{
	return "DevaInvalidInputException: ";
}
