#define VK_USE_PLATFORM_WIN32_KHR

#include "Surface.hpp"
#include "../../Window/ImplWindow.hpp"



using namespace DevaFramework;

Surface::Surface(const Window &wnd)
{
	auto implwnd = wnd.getImpl().lock();
	auto os_prop = implwnd->getOSProperties();
	VkWin32SurfaceCreateInfoKHR info;
	info.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	info.hinstance = os_prop.impl_win32_instance;
	info.hwnd = os_prop.impl_win32_window;
	
}