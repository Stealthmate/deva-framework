#include "Surface.hpp"
#include "../../Window/Window.hpp"

using namespace DevaFramework;

#ifdef VK_USE_PLATFORM_WIN32_KHR
#define VkSurfaceCreateInfoKHR VkWin32SurfaceCreateInfoKHR
#define SURFACE_STYPE VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR
#endif
#ifdef VK_USE_PLATFORM_XLIB_KHR
#define VkSurfaceCreateInfoKHR VkXlibSurfaceCreateInfoKHR
#define SURFACE_STYPE VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR
#endif

Surface::Surface(const Window &wnd)
{
	auto os_prop = wnd.getOSHandles();
	VkSurfaceCreateInfoKHR info;
	info.sType = SURFACE_STYPE;
#ifdef VK_USE_PLATFORM_WIN32_KHR
	info.hinstance = (HINSTANCE) os_prop->win32_hinstance();
	info.hwnd = (HWND) os_prop->win32_hwnd();
#endif
#ifdef VK_USE_PLATFORM_XLIB_KHR
	info.dpy =(Display*) os_prop->xlib_dpy();
	info.window = (::Window) os_prop->xlib_window();
#endif
	
}