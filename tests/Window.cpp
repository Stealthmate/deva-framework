#include "../src/Window/Window.hpp"

#include <iostream>

int main()
{
	using namespace DevaFramework;
	Window &wnd = Window::createWindow(800, 600, "IT'S WORKING!!!");
	while (!wnd.shouldClose())
	{
		wnd.update();
	}
}