#define VK_USE_PLATFORM_WIN32_KHR

#include "Surface.hpp"
#include "../../Window/Window.hpp"

using namespace DevaFramework;

Surface::Surface(const Window &wnd)
{
	auto os_prop = wnd.getOSHandles();
	VkWin32SurfaceCreateInfoKHR info;
	info.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	info.hinstance = (HINSTANCE) os_prop->win32_hinstance();
	info.hwnd = (HWND) os_prop->win32_hwnd();
	
}