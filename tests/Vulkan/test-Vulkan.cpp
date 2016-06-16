#define DEVA_FRAMEWORK_MASTER_H
#include "../src/Window/Window_new.hpp"

using namespace DevaFramework;

int main()
{
	Window &wnd = Window::openWindow(800, 600, "Vulkan!");
}