#ifndef DEVA_FRAMEWORK_WINDOW_WIN32_IMPL_EVENT_INFO_HPP
#define DEVA_FRAMEWORK_WINDOW_WIN32_IMPL_EVENT_INFO_HPP

#include "../WindowObserver.hpp"

#ifdef DEVA_OS_WIN32
#include <windows.h>
#endif 

namespace DevaFramework
{
	struct InputEventInfo
	{
#ifdef DEVA_OS_WIN32
		RAWINPUT *inputData;
#endif
	};
}


#endif //DEVA_FRAMEWORK_WINDOW_WIN32_IMPL_EVENT_INFO_HPP