#include "WindowObserver.hpp"

using namespace DevaFramework;

DevaFramework::WindowObserver::WindowObserver() : windowListeners() {}

void WindowObserver::attachListener(std::shared_ptr<WindowEventListener> inputlstnr)
{
	this->windowListeners.push_back(inputlstnr);
}