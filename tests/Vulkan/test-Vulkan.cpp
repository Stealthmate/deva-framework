#include <Deva.hpp>

using namespace DevaFramework;

struct MyListener : public WindowEventListener
{
	virtual bool onKeyEvent(WindowEventStruct_KeyEvent info)
	{
		return true;
	}
};

int main()
{
	try
	{
		auto lstnr = std::shared_ptr<MyListener>(new MyListener());
		Window &wnd = Window::openWindow(800, 600, "Deva: test-Window");
		wnd.getEventObserver().attachListener(
		{WindowEvent::EVENT_KEY_DOWN, WindowEvent::EVENT_KEY_UP}, std::move(lstnr));
		while (wnd.update());
	}
	catch (DevaFailureException &ex)
	{
		DevaLogger::err.println(ex.what());
	}
}