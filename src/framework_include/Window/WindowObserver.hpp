#ifndef DEVA_FRAMEWORK_WINDOW_WINDOW_OBSERVER_H
#define DEVA_FRAMEWORK_WINDOW_WINDOW_OBSERVER_H

#include "Config.hpp"

#include "Events.hpp"
#include "WindowEventListener.hpp"

#include <unordered_map>
#include <vector>
#include <memory>

namespace DevaFramework
{
	class Window;

	class WindowObserver
	{
	private:
		std::unordered_map<WindowEvent, std::vector<std::shared_ptr<WindowEventListener>>> event_listeners;

	public:
		DEVA_FRAMEWORK_API WindowObserver();

		DEVA_FRAMEWORK_API void attachListener(WindowEvent evt, std::shared_ptr<WindowEventListener> &&evtlstnr);
		DEVA_FRAMEWORK_API void attachListener(
			std::initializer_list<WindowEvent> evts, 
			std::shared_ptr<WindowEventListener> &&evtlstnr);
		DEVA_FRAMEWORK_API void attachListeners(WindowEvent evt, std::initializer_list<std::shared_ptr<WindowEventListener>&&> listeners);

		DEVA_FRAMEWORK_API void fire(Window& wnd, std::shared_ptr<WindowEventStruct> evt);
	};
}

#endif //DEVA_FRAMEWORK_WINDOW_WINDOW_OBSERVER_H