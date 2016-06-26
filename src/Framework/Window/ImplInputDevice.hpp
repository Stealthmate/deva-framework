#ifndef DEVA_FRAMEWORK_WINDOW_IMPL_INPUT_DEVICE_HPP
#define DEVA_FRAMEWORK_WINDOW_IMPL_INPUT_DEVICE_HPP

#include "Config.hpp"

#include "InputDevice.hpp"

#ifdef DEVA_OS_WIN32
#include <windows.h>
#endif

namespace DevaFramework
{
	class ImplInputDevice
	{
#ifdef DEVA_OS_WIN32
		HANDLE handle;
	public:

		virtual void parseInput(const RAWINPUT * input);

#endif
	};

}

#endif //DEVA_FRAMEWORK_WINDOW_IMPL_INPUT_DEVICE_HPP
