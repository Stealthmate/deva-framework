#include <DevaFramework\Include\Core.hpp>
#include <DevaFramework\Include\Window.hpp>

using namespace DevaFramework;
namespace
{
	const char* TEST_DESCRIPTION =
		R"description(Test Description:
	This test should open an empty window. The window should close when Escape is pressed.)description";

	Window* wnd;

	struct MyListener : public WindowEventListener
	{
		/*virtual bool onKeyEvent(WindowEventStruct_KeyEvent info)
		{
			if(info.key == Key::KEY_ESCAPE) wnd->close();
			return true;
		}*/
	};
}


int main()
{
	/*for (auto i = 0; i <= GraphicsState::getPhysicalDeviceCount() - 1;i++)
	{
		DevaLogger::log.println(GraphicsState::getPhysicalDevice(i).to_string());
	}

	DevaLogger::log.println(TEST_DESCRIPTION);

	wnd = &Window::openWindow(800, 600, "Deva: test-Window");
	DevaLogger::log.println("Opened window.");

	auto lstnr = std::shared_ptr<MyListener>(new MyListener());
	wnd->getEventObserver().attachListener(WindowEvent::EVENT_KEY_DOWN, std::move(lstnr));
	DevaLogger::log.println("Attached listener.");


	while (wnd->update());

	DevaLogger::log.println("Test successful.");*/
}


/*
namespace DEVA_TEST_WINDOW {

	

	using namespace DevaFramework;

	void OnKey(Window &win, Key k, InputAction ia, int modmask)
	{
		if (k == Key::KEY_ESCAPE) win.close();
	}
}

using namespace DEVA_TEST_WINDOW;

int main()
{

	Window &wnd = Window::createWindow(800, 600, "test-Window");
	Window::setCurrentWindow(wnd);
	wnd.setOnKeyActionCallback(OnKey);
	
	while (!wnd.shouldClose())
	{
		wnd.update();
	}

	DevaLogger::log.println("Test successful.");
	DevaLogger::log.println("Terminating");
}*/