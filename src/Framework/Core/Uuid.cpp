#include "Uuid.hpp"
#include "DevaLogger.hpp"
using namespace DevaFramework;

const Uuid Uuid::NULL_ID = Uuid(Guid());

Uuid::Uuid() : uuid(GuidGenerator().newGuid()) {}

Uuid::Uuid(Guid guid) : uuid(guid) {}

Uuid::operator std::string() const
{
	std::stringstream ss;
	ss << uuid;
	return ss.str();
}