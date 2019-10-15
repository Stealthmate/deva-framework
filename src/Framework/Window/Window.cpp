#include "ImplWindow.hpp"

#include <vector>

using namespace DevaFramework;

namespace
{
	static std::vector<std::shared_ptr<Window>> window_list;
}

void* OSHandles::win32_hinstance() const
{
	LOG.e("Called OSHandles::win32_hinstance default implementation. Are you trying to get OS parameters for a different system?");
	return nullptr;
}

void* OSHandles::win32_hwnd() const
{
	LOG.e("Called OSHandles::win32_hwnd default implementation. Are you trying to get OS parameters for a different system?");
	return nullptr;
}

void* OSHandles::xcb_connection() const
{
	LOG.e("Called OSHandles::xcb_connection default implementation. Are you trying to get OS parameters for a different system?");
	return nullptr;
}

void* OSHandles::xcb_window() const
{
	LOG.e("Called OSHandles::xcb_window default implementation. Are you trying to get OS parameters for a different system?");
	return nullptr;
}

void* OSHandles::xlib_dpy() const
{
	LOG.e("Called OSHandles::xlib_dpy default implementation. Are you trying to get OS parameters for a different system?");
	return nullptr;
}

void* OSHandles::xlib_window() const
{
	LOG.e("Called OSHandles::xlib_window default implementation. Are you trying to get OS parameters for a different system?");
	return nullptr;
}


std::shared_ptr<Window> Window::openWindow(uint32_t width, uint32_t height, const std::string &name)
{
	window_list.push_back(std::shared_ptr<Window>(new Window(width, height, name)));
	LOG.i(strf(window_list[window_list.size() - 1]->impl->surface_width) + " \n");
	return window_list[window_list.size() - 1];
}

Window::Window(uint32_t width, uint32_t height, const std::string &name)
	:impl(new ImplWindow(this, width, height, name))
{}

Window::Window(Window &&wnd) : impl(std::move(wnd.impl))
{}

Window::~Window() = default;

Window& Window::operator=(Window &&wnd) = default;

WindowObserver& Window::getEventObserver()
{
	return this->impl->getEventObserver();
}

unsigned int Window::getWidth() const
{
	return this->impl->getWidth();
}

unsigned int Window::getHeight() const 
{
	return this->impl->getHeight();
}

bool Window::update()
{
	return this->impl->update();
}

void Window::close()
{
	this->impl->close();
}

void* Window::getUserData() const
{
	return this->impl->getUserData();
}

void Window::setUserData(void *userData)
{
	this->impl->setUserData(userData);
}

std::unique_ptr<OSHandles> Window::getOSHandles() const
{
	return std::move(this->impl->getOSHandles());
}