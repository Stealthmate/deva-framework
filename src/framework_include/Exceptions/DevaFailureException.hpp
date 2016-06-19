#ifndef DEVA_FRAMEWORK_SYSTEM_EXCEPTIONS_DEVA_FAILURE_EXCEPTION_H
#define DEVA_FRAMEWORK_SYSTEM_EXCEPTIONS_DEVA_FAILURE_EXCEPTION_H
 
#include "DevaException.hpp"

namespace DevaFramework
{
	struct DevaFailureException : public DevaException
	{
		const std::string callee;
		const std::string caller;

		DEVA_FRAMEWORK_API DevaFailureException(
			const std::string &description,
			const std::string &callee,
			const std::string &caller);
	};
}

#endif //DEVA_FRAMEWORK_SYSTEM_EXCEPTIONS_DEVA_INTERNAL_FAILURE_EXCEPTION_H