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
	class DevaInvalidInputException;
	class DevaInvalidArgumentException;
	class DevaProgrammerErrorException;
	class DevaExternalFailureException;
	

	//Definitions

	class DevaException : public std::exception 
	{
	protected:
		DEVA_FRAMEWORK_API virtual const std::string getStamp() const;

	public:

		const std::string description;

		DEVA_FRAMEWORK_API DevaException();
		DEVA_FRAMEWORK_API DevaException(const std::string &description);

		DEVA_FRAMEWORK_API virtual const char* what() const;
	};

#define __DEVA_EXCEPTION_SIMPLE(name) \
class name  : public DevaException \
{ \
public: \
	name() : DevaException() {} \
	name(const std::string &description) : DevaException(description) {} \
protected: \
	inline virtual const std::string getStamp() const { return #name; } \
}; \

	__DEVA_EXCEPTION_SIMPLE(DevaInvalidInputException);
	__DEVA_EXCEPTION_SIMPLE(DevaProgrammerErrorException);
	__DEVA_EXCEPTION_SIMPLE(DevaInvalidArgumentException);


	class DevaExternalFailureException : public DevaException
	{
	public:

		const std::string external_dependency;
		const std::string failed_external_function;
		const std::string failed_internal_function;

		DEVA_FRAMEWORK_API DevaExternalFailureException(
			const std::string& description,
			const std::string& external_dependency,
			const std::string& failed_external_function,
			const std::string& failed_internal_function);

		DEVA_FRAMEWORK_API virtual const char* what() const;
	};

}

#endif //DEVA_FRAMEWORK_SYSTEM_EXCEPTIONS_H