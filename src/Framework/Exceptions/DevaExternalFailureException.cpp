#include "DevaExternalFailureException.hpp"

using namespace DevaFramework;

namespace
{
	const std::string DEVA_EXTERNAL_FAILURE_EXCEPTION = "DevaExternalFailureException";

	std::string buildFullDescription(
		const std::string &stamp,
		const std::string &description,
		const std::string &failed_callee,
		const std::string &failed_caller,
		const std::string &failed_external
	)
	{
		std::string str = stamp + ": " + description;
		str += "\n1:\tExternal dependency " + failed_external + " failed.";
		str += "\n1:\tFailed call to " + failed_callee;
		str += "\n2:\tfrom " + failed_caller;
		return str;
	}

}

DevaFramework::DevaExternalFailureException::DevaExternalFailureException(
	const std::string & description, 
	const std::string & failed_callee, 
	const std::string & failed_caller,
	const std::string &failed_external)
	: DevaException(DEVA_EXTERNAL_FAILURE_EXCEPTION, description, 
		buildFullDescription(DEVA_EXTERNAL_FAILURE_EXCEPTION, description, failed_callee, failed_caller, failed_external)),
	failed_callee(failed_callee), failed_caller(failed_caller), failed_external(failed_external) {}