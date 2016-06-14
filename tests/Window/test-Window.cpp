#include "../../src/Deva.hpp"

namespace DEVA_TEST_WINDOW {

	const char* TEST_DESCRIPTION = 
		R"description(Test Description:
	This test should open an empty window. The window should close when Escape is pressed.)description";

	using namespace DevaFramework;

	void OnKey(Window &win, Key k, InputAction ia, int modmask)
	{
		if (k == Key::KEY_ESCAPE) win.close();
	}
}

using namespace DEVA_TEST_WINDOW;

int main()
{
	DEVA_INIT();

	Logger::println(TEST_DESCRIPTION);

	Window &wnd = Window::createWindow(800, 600, "test-Window");
	Window::setCurrentWindow(wnd);
	wnd.setOnKeyActionCallback(OnKey);
	
	while (!wnd.shouldClose())
	{
		wnd.update();
	}

	Logger::println("Test successful.");
	Logger::println("Terminating");
}