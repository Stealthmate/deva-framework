#include "DevaProgrammerErrorException.hpp"

using namespace DevaFramework;

namespace
{
	const std::string DEVA_PROGRAMMER_ERROR_EXCEPTION = "DevaProgrammerErrorException";

	std::string buildFullDescription(
		const std::string &stamp,
		const std::string &description,
		const std::string &what_was_done,
		const std::string &what_to_do,
		const std::string &what_not_to_do
	)
	{
		std::string str = stamp + ": " + description;
		str += "\n1:\tYou (the programmer) have made a mistake! " + what_was_done;
		str += "\n2:\tYou should do " + what_to_do;
		str += "\n3:\tand NOT do " + what_not_to_do;
		return str;
	}

}

DevaFramework::DevaProgrammerErrorException::DevaProgrammerErrorException(
	const std::string &description,
	const std::string &what_was_done,
	const std::string &what_to_do,
	const std::string &what_not_to_do)
	: DevaException(description),
	what_was_done(what_was_done),
	what_to_do(what_to_do),
	what_not_to_do(what_not_to_do) {}