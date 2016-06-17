#include "DevaFailureException.hpp"

using namespace DevaFramework;

namespace
{
	const std::string DEVA_FAILURE_EXCEPTION = "DevaFailureException";

	std::string buildFullDescription(
		const std::string &stamp,
		const std::string &description,
		const std::string &failed_callee,
		const std::string &failed_caller
	)
	{
		std::string str = stamp + ": " + description;
		str += "\n1:\tFailed call to " + failed_callee;
		str += "\n2:\tfrom " + failed_caller;
		return str;
	}

}

DevaFramework::DevaFailureException::DevaFailureException(const std::string & description, const std::string & failed_callee, const std::string & failed_caller)
	: DevaException(DEVA_FAILURE_EXCEPTION, description, buildFullDescription(DEVA_FAILURE_EXCEPTION, description, failed_callee, failed_caller)), 
	failed_callee(failed_callee), failed_caller(failed_caller) {}