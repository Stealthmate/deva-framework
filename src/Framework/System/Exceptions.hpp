#ifndef DEVA_FRAMEWORK_SYSTEM_EXCEPTIONS_H
#define DEVA_FRAMEWORK_SYSTEM_EXCEPTIONS_H

#include "Config.hpp"

#include <exception>

namespace DevaFramework
{
	//Declarations

	//Base
	class DevaException;

	//Specific
	struct DevaInvalidInputException;
	struct DevaInvalidArgumentException;

	struct DevaProgrammerErrorException;

	struct DevaFailureException;
	struct DevaExternalFailureException;
	
	//Definitions

	class DevaException : public std::exception 
	{

	protected:

		const std::string full_description;

		DEVA_FRAMEWORK_API DevaException(const std::string &stamp, const std::string &description, const std::string &full_description);

	public:

		const std::string stamp;
		const std::string description;

		DEVA_FRAMEWORK_API DevaException();
		DEVA_FRAMEWORK_API DevaException(const std::string &description);

		DEVA_FRAMEWORK_API virtual const char* what() const final;
	};

#define __DEVA_EXCEPTION_SIMPLE(name) \
struct name  : public DevaException \
{ \
	name() : DevaException() {} \
	name(const std::string &description) : DevaException(description) {} \
protected: \
}; \

	__DEVA_EXCEPTION_SIMPLE(DevaInvalidInputException);
	__DEVA_EXCEPTION_SIMPLE(DevaInvalidArgumentException);

}

#include "Exceptions/DevaFailureException.hpp"
#include "Exceptions/DevaExternalFailureException.hpp"
#include "Exceptions/DevaProgrammerErrorException.hpp"

#endif //DEVA_FRAMEWORK_SYSTEM_EXCEPTIONS_H