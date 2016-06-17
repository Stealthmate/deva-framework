#include "../Input.hpp"

#include <map>
#include <windows.h>

namespace DevaFramework
{

	typedef WPARAM WinKey;
	typedef DevaFramework::Key DevaKey;

	std::map<WinKey, DevaKey> SUPPORTED_KEYS =
	{
		{VK_ESCAPE, DevaKey::KEY_ESCAPE},
	};
}