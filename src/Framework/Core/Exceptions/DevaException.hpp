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
		DEVA_FRAMEWORK_API DevaException(const char * description) : DevaException(std::string(description)) {}

		DEVA_FRAMEWORK_API 
			const char* what() const noexcept final override;
		DEVA_FRAMEWORK_API virtual std::string getStamp() const final;
	};

#define SIMPLE_EXCEPT(name) \
struct name  : public DevaException \
{ \
	name(const std::string &description) : DevaException(description) {} \
protected: \
}; \

	SIMPLE_EXCEPT(DevaInvalidInputException);
	SIMPLE_EXCEPT(DevaInvalidArgumentException);
	SIMPLE_EXCEPT(DevaProgrammerErrorException);
	SIMPLE_EXCEPT(DevaFailureException);
}
#undef SIMPLE_EXCEPT

#endif //DEVA_FRAMEWORK_EXCEPTIONS_DEVA_EXCEPTION_HPP
