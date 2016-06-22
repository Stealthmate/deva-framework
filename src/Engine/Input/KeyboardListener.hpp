#ifndef DEVA_ENGINE_INPUT_KEYBOARD_LISTENER_HPP
#define DEVA_ENGINE_INPUT_KEYBOARD_LISTENER_HPP

#include "../Config.hpp"

#include <unordered_map>
#include <memory>

namespace DevaEngine
{
	struct KeyboardInputListener : private DevaFramework::WindowEventListener
	{
		DEVA_ENGINE_API virtual bool onKeyPress(DevaFramework::Key k, uint8_t mods) = 0;
		DEVA_ENGINE_API virtual bool onKeyRepeat(DevaFramework::Key k, uint8_t mods) = 0;
		DEVA_ENGINE_API virtual bool onKeyRelease(DevaFramework::Key k, uint8_t mods) = 0;
	};
}


#endif //DEVA_ENGINE_INPUT_KEYBOARD_LISTENER_HPP