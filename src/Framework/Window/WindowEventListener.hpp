#ifndef DEVA_FRAMEWORK_WINDOW_INPUT_LISTENER_HPP
#define DEVA_FRAMEWORK_WINDOW_INPUT_LISTENER_HPP

#include "Config.hpp"

#include "Input.hpp"

namespace DevaFramework
{
	//Interface
	struct WindowEventListener
	{
		DEVA_FRAMEWORK_API virtual bool onKeyDown(Key k);
		DEVA_FRAMEWORK_API virtual bool onKeyUp(Key k);

		DEVA_FRAMEWORK_API virtual bool onMouseMove();
		DEVA_FRAMEWORK_API virtual bool onMouseButtonDown();
		DEVA_FRAMEWORK_API virtual bool onMouseButtonClick();
		DEVA_FRAMEWORK_API virtual bool onMouseButtonUp();
	};
}


#endif //DEVA_FRAMEWORK_WINDOW_INPUT_LISTENER_HPP