#define VK_USE_PLATFORM_WIN32_KHR

#include "../ImplWindow.hpp"

#ifndef DEVA_OS_WIN32
#error "Platform not supported."
#else

#include "../../Exceptions.hpp"

#include "../../DevaLogger.hpp"

#include "../../Graphics/Vulkan/VulkanInstance.hpp"

//#include "impl_keycode_mapping.inl"
#include "impl_win32_EventInfo.hpp"


#include <map>
#include <memory>

using namespace DevaFramework;

using ImplWindow = Window::ImplWindow;

namespace
{

	uint64_t impl_win32_class_id_counter = 0;

	RAWINPUTDEVICE ACCEPTED_INPUT_DEVICES[] = 
	{
		{0x01, 0x02, 0, 0}, //Mouse
		{0x01, 0x06, 0, 0}, //Keyboard
		{0x01, 0x05, 0, 0}, //DirectInput Joystick
	};

	enum ExType
	{
		DEVA_FAILURE_EXCEPTION = 1,
	};

	bool init_call = false;

	typedef std::pair<ExType, std::shared_ptr<DevaException>> DelayedException;
	DelayedException ex;

	void downcastExAndThrow(const DelayedException &ex)
	{
		switch (ex.first)
		{
		case ExType::DEVA_FAILURE_EXCEPTION: 
		{
			throw *static_cast<DevaFailureException*>(ex.second.get());
		}
		}
	}

}

LRESULT CALLBACK DevaFramework::WindowsEventHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (init_call) return DefWindowProc(hWnd, uMsg, wParam, lParam);
	ImplWindow &current_wnd = *reinterpret_cast<ImplWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

	switch (uMsg) {
	case WM_CLOSE:
		//window->sendCloseMsg();
		current_wnd.window_should_run = false;
		break;
	case WM_SIZE:
		// we get here if the window has changed size, we should rebuild most
		// of our window resources before rendering to this window again.
		// ( no need for this because our window sizing by hand is disabled )
		break;
	case WM_INPUT:
	{
		char buffer[sizeof(RAWINPUT)] = {};
		UINT size = sizeof(RAWINPUT);
		GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, buffer, &size, sizeof(RAWINPUTHEADER));

		// extract keyboard raw input data
		RAWINPUT* raw = reinterpret_cast<RAWINPUT*>(buffer);
		WindowEventInfo info;
		info.inputData = raw;
		current_wnd.eventObserver->fire(info);
	}
	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


void ImplWindow::impl_init()
{
	WNDCLASSEX win_class{};

	if (surface_width <= 0 || surface_height <= 0)
		throw DevaInvalidArgumentException(
			"Invalid window dimensions. (width: " + strm(surface_width) + " ; height: " + strm(surface_height) + ")");

	impl_win32_instance = GetModuleHandle(nullptr);
	impl_win32_class_name = this->name + "_" + strm(impl_win32_class_id_counter);
	impl_win32_class_id_counter++;

	// Initialize the window class structure:
	win_class.cbSize = sizeof(WNDCLASSEX);
	win_class.style = CS_HREDRAW | CS_VREDRAW;
	win_class.lpfnWndProc = WindowsEventHandler;
	win_class.cbClsExtra = 0;
	win_class.cbWndExtra = 0;
	win_class.hInstance = impl_win32_instance;
	win_class.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	win_class.hCursor = LoadCursor(NULL, IDC_ARROW);
	win_class.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	win_class.lpszMenuName = NULL;
	win_class.lpszClassName = impl_win32_class_name.c_str();
	win_class.hIconSm = LoadIcon(NULL, IDI_WINLOGO);

	// Register window class:
	if (!RegisterClassEx(&win_class)) {
		throw DevaExternalFailureException("Could not create window.", "Windows", "RegisterClassEx", "DevaFramework::ImplWindow::initOSWindow");
	}

	DWORD ex_style = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
	DWORD style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;

	// Create window with the registered class:
	RECT wr = { 0, 0, LONG(this->surface_width), LONG(this->surface_height) };
	AdjustWindowRectEx(&wr, style, FALSE, style);


	if (!RegisterRawInputDevices(
			ACCEPTED_INPUT_DEVICES, 
			sizeof(ACCEPTED_INPUT_DEVICES) / sizeof(ACCEPTED_INPUT_DEVICES[0]), //Number of elements 
			sizeof(ACCEPTED_INPUT_DEVICES[0]))) {                               //Size of single element
		throw DevaExternalFailureException(
			"Could not register for raw input.", "Windows", "RegisterRawInputDevies", "DevaFramework::ImplWindow::initOSWindow");
	}
	


	init_call = true;
	impl_win32_window = CreateWindowEx(0,
		impl_win32_class_name.c_str(),		// class name
		this->name.c_str(),			// app name
		style,							// window style
		CW_USEDEFAULT, CW_USEDEFAULT,	// x/y coords
		wr.right - wr.left,				// width
		wr.bottom - wr.top,				// height
		NULL,							// handle to parent
		NULL,							// handle to menu
		this->impl_win32_instance,				// hInstance
		NULL);							// no extra parameters

	init_call = false;

	if (!this->impl_win32_window) {
		throw DevaExternalFailureException("Could not create window.", "Windows", "CreateWindowEx", "DevaFramework::ImplWindow::initOSWindow");
	}

	SetWindowLongPtr(this->impl_win32_window, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

	ShowWindow(this->impl_win32_window, SW_SHOW);
	SetForegroundWindow(this->impl_win32_window);
	SetFocus(this->impl_win32_window);
}

void ImplWindow::impl_move(ImplWindow &&wnd)
{
	this->impl_win32_class_name = wnd.impl_win32_class_name;
	wnd.impl_win32_class_name = "";
	this->impl_win32_instance = wnd.impl_win32_instance;
	wnd.impl_win32_instance = NULL;
	this->impl_win32_window = wnd.impl_win32_window;
	wnd.impl_win32_window = NULL;

	SetWindowLongPtr(this->impl_win32_window, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
}

void ImplWindow::impl_deInit()
{
	if (this->impl_win32_instance == NULL) return;
	DestroyWindow(this->impl_win32_window);
	UnregisterClass(this->impl_win32_class_name.c_str(), this->impl_win32_instance);
}

void ImplWindow::impl_update()
{
	if (ex.second) downcastExAndThrow(ex);

	MSG msg;
	if (PeekMessage(&msg, this->impl_win32_window, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void ImplWindow::bindSurface(VulkanInstance &vkinstance)
{
	VkWin32SurfaceCreateInfoKHR info;
	info.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	info.hinstance = this->impl_win32_instance;
	info.hwnd = this->impl_win32_window;

	VkSurfaceKHR surface;

	VkResult result = vkCreateWin32SurfaceKHR(vkinstance.handle, &info, NULL, &surface);
	if (result != VK_SUCCESS)
		throw DevaExternalFailureException("Could not create Vulkan surface.", "vkCreateWin32SurfaceKHR", "ImplWindow::createSurface", "Vulkan");
	
	vkinstance.surface = surface;

}
#endif