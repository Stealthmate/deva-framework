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

	class DevaInvalidInputException  : public DevaException
	{
	public:
		DEVA_FRAMEWORK_API DevaInvalidInputException() : DevaException() {}
		DEVA_FRAMEWORK_API DevaInvalidInputException(const std::string &description) : DevaException(description) {}

	protected:
		DEVA_FRAMEWORK_API virtual const std::string getStamp() const;
	};
}

#endif //DEVA_FRAMEWORK_SYSTEM_EXCEPTIONS_H