#define DEVA_USING_WINDOW
#include "../src/Deva.hpp"

#include <iostream>

using namespace DevaFramework;

void OnKey(Window &win, Key k, InputAction ia, int modmask)
{
	if (k == Key::KEY_ESCAPE) win.close();
}

int main()
{
	DEVA_INIT();

	Window &wnd = Window::createWindow(800, 600, "IT'S WORKING!!!");
	Window::setCurrentWindow(wnd);
	wnd.setOnKeyActionCallback(OnKey);


	while (!wnd.shouldClose())
	{
		wnd.update();
	}
}