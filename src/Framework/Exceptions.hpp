#ifndef DEVA_FRAMEWORK_SYSTEM_EXCEPTIONS_H
#define DEVA_FRAMEWORK_SYSTEM_EXCEPTIONS_H

#include "Config.hpp"

#include <exception>

#include "Exceptions/DevaFailureException.hpp"
#include "Exceptions/DevaExternalFailureException.hpp"
#include "Exceptions/DevaProgrammerErrorException.hpp"

namespace DevaFramework
{

#define __DEVA_EXCEPTION_SIMPLE(name) \
struct name  : public DevaException \
{ \
	name(const std::string &description) : DevaException(description) {} \
protected: \
}; \

	__DEVA_EXCEPTION_SIMPLE(DevaInvalidInputException);
	__DEVA_EXCEPTION_SIMPLE(DevaInvalidArgumentException);
}

#endif //DEVA_FRAMEWORK_SYSTEM_EXCEPTIONS_H
