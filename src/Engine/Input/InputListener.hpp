#ifndef DEVA_ENGINE_INPUT_INPUT_LISTENER_HPP
#define DEVA_ENGINE_INPUT_INPUT_LISTENER_HPP

#include "../Config.hpp"

#include "../DevaEngineInstance.hpp"
#include "KeyboardListener.hpp"

namespace DevaEngine
{
	class InputListener
	{
		std::shared_ptr<KeyboardInputListener> keyboardListener;

	public:

		DEVA_ENGINE_API InputListener();

		DEVA_ENGINE_API void setKeyboardListener(const std::shared_ptr<KeyboardInputListener> &kblstnr);

	};
}

#endif //DEVA_ENGINE_INPUT_INPUT_LISTENER_HPP