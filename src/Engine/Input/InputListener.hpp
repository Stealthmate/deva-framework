#ifndef DEVA_ENGINE_INPUT_INPUT_LISTENER_HPP
#define DEVA_ENGINE_INPUT_INPUT_LISTENER_HPP

#include "../Config.hpp"

#include "KeyboardListener.hpp"
#include "InputFunction.hpp"

namespace DevaEngine
{
	const uint8_t MOD_ALT = 0x01;
	const uint8_t MOD_CTRL = 0x02;
	const uint8_t MOD_SUPER = 0x03;

	class InputListener
	{
		std::unordered_map<DevaFramework::Key, InputFunction> keymap;

	public:

		DEVA_ENGINE_API InputListener() = default;
		DEVA_ENGINE_API InputListener(InputListener &&lstnr) = default;
	};
}

#endif //DEVA_ENGINE_INPUT_INPUT_LISTENER_HPP