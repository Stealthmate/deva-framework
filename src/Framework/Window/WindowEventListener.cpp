#include "WindowEventListener.hpp"

using namespace DevaFramework;

bool WindowEventListener::onKeyDown(Key k) { return false; }
bool WindowEventListener::onKeyUp(Key k) { return false; }

bool WindowEventListener::onMouseMove(signed int x, signed int y) { return false; }
bool WindowEventListener::onMouseWheelMove(signed int motion) { return false; }
bool WindowEventListener::onMouseButtonDown(MouseButton mb) { return false; }
bool WindowEventListener::onMouseButtonClick(MouseButton mb) { return false; }
bool WindowEventListener::onMouseButtonUp(MouseButton mb) { return false; }
