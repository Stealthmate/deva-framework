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

	DevaLogger::log.println(TEST_DESCRIPTION);

	Window &wnd = Window::createWindow(800, 600, "test-Window");
	Window::setCurrentWindow(wnd);
	wnd.setOnKeyActionCallback(OnKey);
	
	while (!wnd.shouldClose())
	{
		wnd.update();
	}

	DevaLogger::log.println("Test successful.");
	DevaLogger::log.println("Terminating");
}