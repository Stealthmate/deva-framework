#ifndef DEVA_FRAMEWORK_WINDOW_WINDOW_OBSERVER_H
#define DEVA_FRAMEWORK_WINDOW_WINDOW_OBSERVER_H

#include "Config.hpp"

#include "Events.hpp"
#include "WindowEventListener.hpp"
#include "InputListener.hpp"

#include <unordered_map>
#include <vector>
#include <memory>

namespace DevaFramework
{

	class WindowObserver
	{
	private:
		std::unordered_map<WindowEvent, std::vector<std::shared_ptr<WindowEventListener>>> event_listeners;
		std::vector<std::shared_ptr<InputListener>> inputListeners;

	public:
		DEVA_FRAMEWORK_API WindowObserver();

		DEVA_FRAMEWORK_API void attachListener(WindowEvent evt, std::shared_ptr<WindowEventListener> &&evtlstnr);
		DEVA_FRAMEWORK_API void attachListener(
			std::initializer_list<WindowEvent> evts, 
			std::shared_ptr<WindowEventListener> &&evtlstnr);
		DEVA_FRAMEWORK_API void attachListeners(WindowEvent evt, std::initializer_list<std::shared_ptr<WindowEventListener>&&> listeners);

		DEVA_FRAMEWORK_API void fire(std::shared_ptr<EventInfo> evt);
		DEVA_FRAMEWORK_API void fire_InputEvent(const InputEventInfo &info);
		
		DEVA_FRAMEWORK_API void addInputListener(std::shared_ptr<InputListener> inputlstnr);
	};
}

#endif //DEVA_FRAMEWORK_WINDOW_WINDOW_OBSERVER_H