#ifndef DEVA_FRAMEWORK_WINDOW_WINDOW_EVENT_LISTENER_H
#define DEVA_FRAMEWORK_WINDOW_WINDOW_EVENT_LISTENER_H

#include "Config.hpp"

#include "Events.hpp"
#include "WindowEventInfo.hpp"


namespace DevaFramework
{
	class Window;

	class WindowEventListener
	{
	public:
		//Method declarations for supported events
		DEVA_FRAMEWORK_API virtual bool onKeyEvent(KeyEventInfo evtinfo);
	};
}

#endif //DEVA_FRAMEWORK_WINDOW_WINDOW_EVENT_LISTENER_H