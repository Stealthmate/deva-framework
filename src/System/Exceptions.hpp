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

		DEVA_SYSTEM_API virtual const std::string getStamp() const;

	public:
		DEVA_SYSTEM_API DevaException();
		DEVA_SYSTEM_API DevaException(const std::string &description);

		DEVA_SYSTEM_API virtual const char* what() const;
	};

	class DevaInvalidInputException  : public DevaException
	{
	public:
		DEVA_SYSTEM_API DevaInvalidInputException() : DevaException() {}
		DEVA_SYSTEM_API DevaInvalidInputException(const std::string &description) : DevaException(description) {}

	protected:
		DEVA_SYSTEM_API virtual const std::string getStamp() const;
	};
}

#endif //DEVA_FRAMEWORK_SYSTEM_EXCEPTIONS_H