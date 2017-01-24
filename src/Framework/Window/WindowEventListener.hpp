#ifndef DEVA_FRAMEWORK_WINDOW_INPUT_LISTENER_HPP
#define DEVA_FRAMEWORK_WINDOW_INPUT_LISTENER_HPP
//asd
#include "Config.hpp"

#include "Input.hpp"

namespace DevaFramework
{
	//Interface
	struct WindowEventListener
	{
		DEVA_FRAMEWORK_API virtual bool onKeyDown(Key k);
		DEVA_FRAMEWORK_API virtual bool onKeyUp(Key k);

		DEVA_FRAMEWORK_API virtual bool onMouseMove(signed int x, signed int y);
		DEVA_FRAMEWORK_API virtual bool onMouseWheelMove(signed int motion);
		DEVA_FRAMEWORK_API virtual bool onMouseButtonDown(MouseButton mb);
		DEVA_FRAMEWORK_API virtual bool onMouseButtonClick(MouseButton mb);
		DEVA_FRAMEWORK_API virtual bool onMouseButtonUp(MouseButton mb);
	};
}


#endif //DEVA_FRAMEWORK_WINDOW_INPUT_LISTENER_HPP