#include "DevaUnsupportedOperationException.hpp"
#include "../DevaLogger.hpp"

using namespace DevaFramework;

DevaUnsupportedOperationException::DevaUnsupportedOperationException(const std::string &unsupported) 
: DevaException(strformat("Unsupported operation: {}", unsupported)) {

}