#include "ImplWindow.hpp"

#include "../DevaLogger.hpp"

#include <vector>

using namespace DevaFramework;
using ImplWindow = Window::ImplWindow;

ImplWindow::ImplWindow(Window *wnd, uint32_t width, uint32_t height, const std::string &name)
	:wnd(wnd), surface_width(width), surface_height(height), name(name), eventObserver(std::shared_ptr<WindowObserver>(new WindowObserver()))
{
	this->impl_init();
}

ImplWindow::ImplWindow(ImplWindow &&implwnd, Window* new_wnd)
	:wnd(new_wnd), 
	surface_width(implwnd.surface_width), 
	surface_height(implwnd.surface_height), 
	name(implwnd.name), 
	eventObserver(std::move(implwnd.eventObserver)),
	userData(implwnd.userData)
{
	this->impl_move(std::move(implwnd));
	implwnd.wnd = nullptr;
	implwnd.surface_width = 0;
	implwnd.surface_height = 0;
	implwnd.name = "";
	implwnd.userData = nullptr;
}

ImplWindow::~ImplWindow()
{
	if(wnd != nullptr) impl_deInit();
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

void* ImplWindow::getUserData() const
{
	return userData;
}

void ImplWindow::setUserData(void *userData)
{
	this->userData = userData;
}