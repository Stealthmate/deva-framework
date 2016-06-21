#ifndef DEVA_ENGINE_INPUT_KEYBOARD_LISTENER_HPP
#define DEVA_ENGINE_INPUT_KEYBOARD_LISTENER_HPP

#include "../Config.hpp"

#include <DevaFramework/Window/WindowEventListener.hpp>

#include <unordered_map>
#include <memory>

namespace DevaEngine
{
	typedef DevaFramework::Key Key;

	struct KeyboardInputListener : private DevaFramework::WindowEventListener
	{
		DEVA_ENGINE_API virtual bool onKeyPress(Key k) = 0;
		DEVA_ENGINE_API virtual bool onKeyRepeat(Key k) = 0;
		DEVA_ENGINE_API virtual bool onKeyRelease(Key k) = 0;
	};
}


#endif //DEVA_ENGINE_INPUT_KEYBOARD_LISTENER_HPP