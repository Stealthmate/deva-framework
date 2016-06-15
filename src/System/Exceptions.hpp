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
	class DevaProgrammerErrorException;
	

	//Definitions

	class DevaException : public std::exception 
	{

		std::string description;

	protected:

		DEVA_FRAMEWORK_API virtual const std::string getStamp() const;

	public:
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
}

#endif //DEVA_FRAMEWORK_SYSTEM_EXCEPTIONS_H