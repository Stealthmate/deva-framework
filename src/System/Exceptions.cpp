#include "Exceptions.hpp"


using namespace DevaFramework;

DevaException::DevaException() : description(getStamp()) {}

DevaException::DevaException(const std::string &description) : description(getStamp() + " " + description) {}

const std::string DevaException::getStamp() const
{
	return "DevaException:";
}

const char* DevaException::what() const
{
	return this->description.c_str();
}

DevaFramework::DevaExternalFailureException::DevaExternalFailureException(
	const std::string & description, 
	const std::string & external_dependency, 
	const std::string & failed_external_function, 
	const std::string & failed_internal_function)
	: DevaException(description),
	external_dependency(external_dependency),
	failed_external_function(failed_external_function),
	failed_internal_function(failed_internal_function) {}

const char* DevaExternalFailureException::what() const
{
	std::string str = getStamp();
	str += description + "\n";
	str += "\tExternal failure of " + external_dependency + "\n";
	str += "\twhen calling function " + failed_external_function + "\n";
	str += "\tfrom function " + failed_internal_function + "\n";

	return str.c_str();
}
