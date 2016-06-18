#ifndef DEVA_FRAMEWORK_SYSTEM_EXCEPTIONS_DEVA_FAILURE_EXCEPTION_H
#define DEVA_FRAMEWORK_SYSTEM_EXCEPTIONS_DEVA_FAILURE_EXCEPTION_H
 
#include "../Config.hpp"
#include "../Exceptions.hpp"

namespace DevaFramework
{
	struct DevaFailureException : public DevaException
	{
		const std::string failed_callee;
		const std::string failed_caller;

		DEVA_FRAMEWORK_API DevaFailureException(
			const std::string &description,
			const std::string &failed_callee,
			const std::string &failed_caller
		);
	};
}

#endif //DEVA_FRAMEWORK_SYSTEM_EXCEPTIONS_DEVA_INTERNAL_FAILURE_EXCEPTION_H