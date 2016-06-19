#ifndef DEVA_FRAMEWORK_EXCEPTIONS_DEVA_EXCEPTION_HPP
#define DEVA_FRAMEWORK_EXCEPTIONS_DEVA_EXCEPTION_HPP

#include "../Config.hpp"

namespace DevaFramework
{
	class DevaException : public std::exception
	{

	protected:

		mutable std::string full_description;
		mutable std::string stamp;

	public:

		const std::string description;

		DEVA_FRAMEWORK_API DevaException(const std::string &description);

		DEVA_FRAMEWORK_API virtual const char* what() const final;
		DEVA_FRAMEWORK_API virtual std::string getStamp() const final;
	};
}

#endif //DEVA_FRAMEWORK_EXCEPTIONS_DEVA_EXCEPTION_HPP