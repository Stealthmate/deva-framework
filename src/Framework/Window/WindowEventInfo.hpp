#ifndef DEVA_FRAMEWORK_WINDOW_WINDOW_EVENT_INFO_H
#define DEVA_FRAMEWORK_WINDOW_WINDOW_EVENT_INFO_H

#include "Config.hpp"

#include "Events.hpp"

#include <memory>

namespace DevaFramework
{
	class Window;
	struct WindowEventStruct
	{
		Window* wnd;
		WindowEvent evt;
	};

	struct WindowEventStruct_KeyEvent : public WindowEventStruct
	{
		Key key;
		uint8_t scancode;
		bool wasPressed;
	};

}

#endif // DEVA_FRAMEWORK_WINDOW_WINDOW_EVENT_INFO_H