#ifndef DEVA_FRAMEWORK_SYSTEM_EXCEPTIONS_DEVA_EXTERNAL_FAILURE_EXCEPTION_H
#define DEVA_FRAMEWORK_SYSTEM_EXCEPTIONS_DEVA_EXTERNAL_FAILURE_EXCEPTION_H

#include "DevaFailureException.hpp"

namespace DevaFramework
{
	struct DevaExternalFailureException : public DevaFailureException
	{
		const std::string external;

		DEVA_FRAMEWORK_API DevaExternalFailureException(
			const std::string &description,
			const std::string &callee,
			const std::string &caller,
			const std::string &external);
	};
}

#endif //DEVA_FRAMEWORK_SYSTEM_EXCEPTIONS_DEVA_EXTERNAL_FAILURE_EXCEPTION_H
