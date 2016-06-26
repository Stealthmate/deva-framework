#include "InputListener.hpp"

#include <DevaFramework/DevaLogger.hpp>

using namespace DevaEngine;

namespace
{
	class DefaultKeyboardListener : public KeyboardInputListener
	{
	public:

		virtual bool onKeyPress(DevaFramework::Key k, uint8_t mods)
		{
			//DevaLogger::log << "Pressed " << k << "\n";
			return true;
		}
		virtual bool onKeyRepeat(DevaFramework::Key k, uint8_t mods)
		{
			//DevaLogger::log << "Held " << k << "\n";
			return true;
		}
		virtual bool onKeyRelease(DevaFramework::Key k, uint8_t mods)
		{
			//DevaLogger::log << "Released " << k << "\n";
			return true;
		}
	};
}

InputListener::InputListener() : keyboardListener(
	std::static_pointer_cast<KeyboardInputListener, DefaultKeyboardListener>
	(std::shared_ptr<DefaultKeyboardListener>(new DefaultKeyboardListener()))), keymap()
{
	keymap = std::unordered_map<DevaFramework::Key, InputFunction>();
}

InputListener::InputListener(InputListener &&lstnr)
	:keyboardListener(std::move(lstnr.keyboardListener)), keymap(std::move(lstnr.keymap))
{

}


void InputListener::setKeyboardListener(const std::shared_ptr<KeyboardInputListener> &kblstnr)
{
	this->keyboardListener = kblstnr;
}

void InputListener::onKeyboardAction(DevaFramework::Key k, KeyboardAction kact, uint8_t mods)
{

	switch (kact)
	{
	case KeyboardAction::KEY_PRESS:
	{
		auto i = keymap.find(k);
		if (i != keymap.end() && !i->second()) this->keyboardListener->onKeyPress(k, mods);
	}
		break;
	case KeyboardAction::KEY_REPEAT:
		this->keyboardListener->onKeyRepeat(k, mods);
		break;
	case KeyboardAction::KEY_RELEASE:
		this->keyboardListener->onKeyRelease(k, mods);
		break;
	}
}

void InputListener::bindKey(DevaFramework::Key k, const InputFunction & func)
{
	auto i = keymap.find(k);
	if (i != keymap.end()) i->second = func;
	else
	{
		keymap.insert({k, func});
	}
}
