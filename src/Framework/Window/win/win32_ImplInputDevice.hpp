#ifndef DEVA_FRAMEWORK_WINDOW_WIN_WIN32_IMPL_INPUT_DEVICE
#define DEVA_FRAMEWORK_WINDOW_WIN_WIN32_IMPL_INPUT_DEVICE

#include "../Config.hpp"

#ifdef DEVA_OS_WIN32

#include "../InputDevice.hpp"

#include <windows.h>

namespace DevaFramework
{
	class ImplInputDevice
	{
		friend class ImplWindow;
		HANDLE handle;

		InputDevice * device;

	public:

		void generateInput();

	};
}


#endif //DEVA_OS_WIN32
#endif //DEVA_FRAMEWORK_WINDOW_WIN_WIN32_IMPL_INPUT_DEVICE