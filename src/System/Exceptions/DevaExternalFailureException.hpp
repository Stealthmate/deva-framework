#ifndef DEVA_FRAMEWORK_SYSTEM_EXCEPTIONS_DEVA_EXTERNAL_FAILURE_EXCEPTION_H
#define DEVA_FRAMEWORK_SYSTEM_EXCEPTIONS_DEVA_EXTERNAL_FAILURE_EXCEPTION_H

#include "../Config.hpp"
#include "../Exceptions.hpp"

namespace DevaFramework
{
	struct DevaExternalFailureException : public DevaException
	{
		const std::string failed_callee;
		const std::string failed_caller;
		const std::string failed_external;

		DEVA_FRAMEWORK_API DevaExternalFailureException(
			const std::string &description,
			const std::string &failed_callee,
			const std::string &failed_caller,
			const std::string &failed_external
		);
	};
}

#endif //DEVA_FRAMEWORK_SYSTEM_EXCEPTIONS_DEVA_EXTERNAL_FAILURE_EXCEPTION_H