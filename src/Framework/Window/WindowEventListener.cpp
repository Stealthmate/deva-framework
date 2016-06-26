#include "WindowEventListener.hpp"

using namespace DevaFramework;

bool WindowEventListener::onKeyDown(Key k)
{
	return false;
}

bool WindowEventListener::onKeyUp(Key k)
{
	return false;
}

bool WindowEventListener::onMouseMove()	{ return false; }
bool WindowEventListener::onMouseButtonDown() { return false; }
bool WindowEventListener::onMouseButtonClick() { return false; }
bool WindowEventListener::onMouseButtonUp() { return false; }
