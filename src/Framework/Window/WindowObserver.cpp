#include "WindowObserver.hpp"

using namespace DevaFramework;

DevaFramework::WindowObserver::WindowObserver() : inputListeners() {}

void WindowObserver::attachInputListener(std::shared_ptr<InputListener> inputlstnr)
{
	this->inputListeners.push_back(inputlstnr);
}