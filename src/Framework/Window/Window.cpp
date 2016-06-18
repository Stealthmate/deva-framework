#include "Window.hpp"

#include "../src/System/DevaLogger.hpp"

#include <vector>

using namespace DevaFramework;

namespace
{
	static std::vector<Window> window_list;
}

Window& Window::openWindow(uint32_t width, uint32_t height, const std::string &name)
{
	Window wnd = Window(width, height, name);
	window_list.push_back(std::move(wnd));
	return window_list[window_list.size() - 1];
}

Window::Window(uint32_t width, uint32_t height, const std::string &name)
	: surface_width(width), surface_height(height), name(name), eventObserver(std::shared_ptr<WindowObserver>(new WindowObserver()))
{
	this->impl_init();
}

Window::Window(Window &&wnd)
	: surface_width(wnd.surface_width), surface_height(wnd.surface_height), name(wnd.name), eventObserver(std::move(wnd.eventObserver))
{
	this->impl_move(std::move(wnd));
	wnd.surface_width = 0;
	wnd.surface_height = 0;
	wnd.name = "";
}

WindowObserver& Window::getEventObserver()
{
	return *this->eventObserver;
}

bool Window::update()
{
	this->impl_update();
	return window_should_run;
}

void Window::close()
{
	this->window_should_run = false;
}

Window::~Window()
{
	impl_deInit();
}


