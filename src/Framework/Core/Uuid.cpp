#include "Uuid.hpp"

using namespace DevaFramework;

Uuid::Uuid() : uuid(GuidGenerator().newGuid()) {}

Uuid::operator std::string() const
{
	std::stringstream ss;
	ss << uuid;
	return ss.str();
}