#include "ImplWindow.hpp"

#include "../DevaLogger.hpp"

#include <vector>

using namespace DevaFramework;
using ImplWindow = Window::ImplWindow;

ImplWindow::ImplWindow(Window &wnd, uint32_t width, uint32_t height, const std::string &name)
	: wnd(wnd), surface_width(width), surface_height(height), name(name), eventObserver(std::shared_ptr<WindowObserver>(new WindowObserver()))
{
	this->impl_init();
}

ImplWindow::ImplWindow(ImplWindow &&implwnd)
	: wnd(implwnd.wnd), surface_width(implwnd.surface_width), surface_height(implwnd.surface_height), name(implwnd.name), eventObserver(std::move(implwnd.eventObserver))
{
	this->impl_move(std::move(implwnd));
	implwnd.surface_width = 0;
	implwnd.surface_height = 0;
	implwnd.name = "";
}

WindowObserver& ImplWindow::getEventObserver()
{
	return *this->eventObserver;
}

bool ImplWindow::update()
{
	this->impl_update();
	return window_should_run;
}

void ImplWindow::close()
{
	this->window_should_run = false;
}

ImplWindow::~ImplWindow()
{
	impl_deInit();
}


