#ifndef DEVA_ENGINE_INPUT_INPUT_LISTENER_HPP
#define DEVA_ENGINE_INPUT_INPUT_LISTENER_HPP

#include "../Config.hpp"

#include "KeyboardListener.hpp"
#include "InputFunction.hpp"

namespace DevaEngine
{
	enum KeyboardAction
	{
		KEY_PRESS,
		KEY_REPEAT,
		KEY_RELEASE
	};

	const uint8_t MOD_ALT = 0x01;
	const uint8_t MOD_CTRL = 0x02;
	const uint8_t MOD_SUPER = 0x03;

	class InputListener
	{
		std::shared_ptr<KeyboardInputListener> keyboardListener;

		std::unordered_map<DevaFramework::Key, InputFunction> keymap;

	public:

		DEVA_ENGINE_API InputListener();
		DEVA_ENGINE_API InputListener(InputListener &&lstnr);

		DEVA_ENGINE_API void setKeyboardListener(const std::shared_ptr<KeyboardInputListener> &kblstnr);

		DEVA_ENGINE_API void onKeyboardAction(DevaFramework::Key k, KeyboardAction kact, uint8_t modifiers);

		DEVA_ENGINE_API void bindKey(DevaFramework::Key k, const InputFunction &func);

		DEVA_ENGINE_API KeyboardInputListener& getKeyboardListener();

	};
}

#endif //DEVA_ENGINE_INPUT_INPUT_LISTENER_HPP