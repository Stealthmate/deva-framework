#include "DevaFailureException.hpp"

using namespace DevaFramework;

namespace
{
	const std::string DEVA_FAILURE_EXCEPTION = "DevaFailureException";
}

DevaFramework::DevaFailureException::DevaFailureException(
	const std::string & description, 
	const std::string & callee, 
	const std::string & caller)
	: DevaException(description), callee(callee), caller(caller) 
{
	stamp = DEVA_FAILURE_EXCEPTION;

	std::string str = stamp + ": " + description;
	str += "\n1:\tFailed call to " + callee;
	str += "\n2:\tfrom " + caller;

	this->full_description = str;
}