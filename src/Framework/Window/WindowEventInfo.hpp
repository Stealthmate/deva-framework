#ifndef DEVA_FRAMEWORK_WINDOW_WINDOW_EVENT_INFO_H
#define DEVA_FRAMEWORK_WINDOW_WINDOW_EVENT_INFO_H

#include "Config.hpp"

#include "Events.hpp"

#include <memory>

namespace DevaFramework
{
	struct InputEventInfo;

	class Window;

	struct EventInfo
	{
		Window* wnd;
		WindowEvent evt;
	};

	struct KeyboardEventInfo : public EventInfo
	{
		Key key;
		bool repeat;
	};

	struct KeyEventInfo : public EventInfo
	{
		Key key;
		uint8_t scancode;
		bool wasPressed;
	};

	struct CharEventInfo : public EventInfo
	{
		uint32_t charcode;
	};

	struct WindowEventStruct_MouseButtonEvent
	{

	};

}

#endif // DEVA_FRAMEWORK_WINDOW_WINDOW_EVENT_INFO_H