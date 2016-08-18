#include "ImplWindow.hpp"

#include "../DevaLogger.hpp"

#include <vector>

using namespace DevaFramework;

namespace
{
	static std::vector<Window> window_list;
}

Window& Window::openWindow(uint32_t width, uint32_t height, const std::string &name)
{
	window_list.push_back(std::move(Window(width, height, name)));
	DevaLogger::log << window_list[window_list.size() - 1].impl->surface_width << " \n";
	return window_list[window_list.size() - 1];
}

Window::Window(uint32_t width, uint32_t height, const std::string &name)
	:impl(new ImplWindow(this, width, height, name))
{}

Window::Window(Window &&wnd) : impl(new ImplWindow(std::move(*wnd.impl), this))
{}

Window::~Window() = default;

Window& Window::operator=(Window &&wnd) = default;

WindowObserver& Window::getEventObserver()
{
	return this->impl->getEventObserver();
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

void Window::bindSurface(VulkanInstance &vkinstance)
{
	this->impl->bindSurface(vkinstance);
}