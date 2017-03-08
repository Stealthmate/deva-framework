#include "DevaExternalFailureException.hpp"

using namespace DevaFramework;

namespace
{
	const std::string DEVA_EXTERNAL_FAILURE_EXCEPTION = "DevaExternalFailureException";
}

DevaFramework::DevaExternalFailureException::DevaExternalFailureException(
	const std::string &external,
	const std::string &description)
	: DevaFailureException(description), external(external) 
{
	stamp = DEVA_EXTERNAL_FAILURE_EXCEPTION;

	this->full_description += "\n3:\tExternal dependency: " + external + " failed.";
}