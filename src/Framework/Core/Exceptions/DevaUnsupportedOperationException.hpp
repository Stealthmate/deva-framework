#ifndef DEVA_FRAMEWORK_CORE_EXCEPTIONS_UNSUPPORTED_OPERATION_EXCEPTION_HPP
#define DEVA_FRAMEWORK_CORE_EXCEPTIONS_UNSUPPORTED_OPERATION_EXCEPTION_HPP

#include "DevaException.hpp"

namespace DevaFramework {

	struct DevaUnsupportedOperationException : public DevaException {

		DEVA_FRAMEWORK_API DevaUnsupportedOperationException(const std::string &operation);

	};

}

#endif // DEVA_FRAMEWORK_CORE_EXCEPTIONS_UNSUPPORTED_OPERATION_EXCEPTION_HPP