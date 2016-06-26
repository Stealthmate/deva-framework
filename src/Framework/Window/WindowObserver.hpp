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
		std::vector<std::shared_ptr<InputListener>> inputListeners;

	public:
		DEVA_FRAMEWORK_API WindowObserver();

		DEVA_FRAMEWORK_API void fire_InputEvent(const InputEventInfo &info);
		
		DEVA_FRAMEWORK_API void attachInputListener(std::shared_ptr<InputListener> inputlstnr);
	};
}

#endif //DEVA_FRAMEWORK_WINDOW_WINDOW_OBSERVER_H