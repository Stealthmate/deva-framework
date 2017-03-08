#ifndef DEVA_FRAMEWORK_EXCEPTIONS_DEVA_INITIALIZATION_FAILURE_EXCEPTION_HPP
#define DEVA_FRAMEWORK_EXCEPTIONS_DEVA_INITIALIZATION_FAILURE_EXCEPTION_HPP

#include "DevaFailureException.hpp"

namespace DevaFramework
{
	struct DevaInitializationFailureException : public DevaFailureException
	{
		const std::string external;

		DEVA_FRAMEWORK_API DevaInitializationFailureException(
			const std::string &description,
			const std::string &callee,
			const std::string &caller,
			const std::string &external);
	};
}

#endif DEVA_FRAMEWORK_EXCEPTIONS_DEVA_INITIALIZATION_FAILURE_EXCEPTION_HPP