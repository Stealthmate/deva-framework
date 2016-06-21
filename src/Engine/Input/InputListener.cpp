#include "InputListener.hpp"

#include <DevaFramework/DevaLogger.hpp>

using namespace DevaEngine;
using namespace DevaFramework;

namespace
{
	class DefaultKeyboardListener : public KeyboardInputListener
	{
	public:

		virtual bool onKeyPress(Key k)
		{
			DevaLogger::log << "Pressed " << k << "\n";
			return true;
		}
		virtual bool onKeyRepeat(Key k)
		{
			DevaLogger::log << "Held " << k << "\n";
			return true;
		}
		virtual bool onKeyRelease(Key k)
		{
			DevaLogger::log << "Released " << k << "\n";
			return true;
		}
	};
}

InputListener::InputListener() : keyboardListener(new DefaultKeyboardListener())
{}


void InputListener::setKeyboardListener(const std::shared_ptr<KeyboardInputListener> &kblstnr)
{
	this->keyboardListener = kblstnr;
}