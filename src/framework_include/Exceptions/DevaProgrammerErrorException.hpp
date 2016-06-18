#ifndef DEVA_FRAMEWORK_SYSTEM_EXCEPTIONS_DEVA_PROGRAMMER_ERROR_EXCEPTION_H
#define DEVA_FRAMEWORK_SYSTEM_EXCEPTIONS_DEVA_PROGRAMMER_ERROR_EXCEPTION_H

#include "../Config.hpp"
#include "../Exceptions.hpp"

namespace DevaFramework
{
	struct DevaProgrammerErrorException : public DevaException
	{
		const std::string what_was_done;
		const std::string what_to_do;
		const std::string what_not_to_do;

		DEVA_FRAMEWORK_API DevaProgrammerErrorException(
			const std::string &description,
			const std::string &what_was_done,
			const std::string &what_to_do,
			const std::string &what_not_to_do
		);
	};
}

#endif //DEVA_FRAMEWORK_SYSTEM_EXCEPTIONS_DEVA_PROGRAMMER_ERROR_EXCEPTION_H