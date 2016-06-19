#include "DevaExternalFailureException.hpp"

using namespace DevaFramework;

namespace
{
	const std::string DEVA_EXTERNAL_FAILURE_EXCEPTION = "DevaExternalFailureException";
}

DevaFramework::DevaExternalFailureException::DevaExternalFailureException(
	const std::string & description, 
	const std::string & callee, 
	const std::string & caller,
	const std::string &external)
	: DevaFailureException(description, callee, caller), external(external) 
{
	stamp = DEVA_EXTERNAL_FAILURE_EXCEPTION;

	this->full_description += "\n3:\tExternal dependency: " + external + " failed.";
}