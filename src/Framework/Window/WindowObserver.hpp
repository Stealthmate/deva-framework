#ifndef DEVA_FRAMEWORK_WINDOW_WINDOW_OBSERVER_H
#define DEVA_FRAMEWORK_WINDOW_WINDOW_OBSERVER_H

#include "Config.hpp"

#include "WindowEventListener.hpp"
#include "WindowEventInfo.hpp"

#include <unordered_map>
#include <vector>
#include <memory>

namespace DevaFramework
{

	class WindowObserver
	{
	private:
		std::vector<std::shared_ptr<WindowEventListener>> windowListeners;

	public:
		DEVA_FRAMEWORK_API WindowObserver();

		DEVA_FRAMEWORK_API void fire(const WindowEventInfo &info);
		
		DEVA_FRAMEWORK_API void attachListener(std::shared_ptr<WindowEventListener> inputlstnr);
	};
}

#endif //DEVA_FRAMEWORK_WINDOW_WINDOW_OBSERVER_H
