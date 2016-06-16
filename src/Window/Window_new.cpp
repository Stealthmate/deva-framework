#include "Window_new.hpp"

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
	: surface_width(width), surface_height(height), name(name)
{
	this->initOSWindow();
}

Window::Window(Window &&wnd)
	: surface_width(wnd.surface_width), surface_height(wnd.surface_height), name(wnd.name)
{
	this->moveOSWindow(std::move(wnd));
	wnd.surface_width = 0;
	wnd.surface_height = 0;
	wnd.name = "";
}

Window::~Window()
{
	deInitOSWindow();
}