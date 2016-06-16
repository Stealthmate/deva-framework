#include "../Window_new.hpp"

#include "../../System/Exceptions.hpp"

#include <assert.h>

#ifndef DEVA_OS_WIN32
#error "Platform not supported."
#else

using namespace DevaFramework;

namespace
{
	LRESULT CALLBACK WindowsEventHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		Window * window = reinterpret_cast<Window*>(
			GetWindowLongPtrW(hWnd, GWLP_USERDATA));

		switch (uMsg) {
		case WM_CLOSE:
			//window->Close();
			return 0;
		case WM_SIZE:
			// we get here if the window has changed size, we should rebuild most
			// of our window resources before rendering to this window again.
			// ( no need for this because our window sizing by hand is disabled )
			break;
		default:
			break;
		}

		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}


}

uint64_t Window::impl_win32_class_id_counter = 0;

void Window::initOSWindow()
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
	win_class.hInstance = impl_win32_instance; // hInstance
	win_class.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	win_class.hCursor = LoadCursor(NULL, IDC_ARROW);
	win_class.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	win_class.lpszMenuName = NULL;
	win_class.lpszClassName = impl_win32_class_name.c_str();
	win_class.hIconSm = LoadIcon(NULL, IDI_WINLOGO);

	// Register window class:
	if (!RegisterClassEx(&win_class)) {
		throw DevaExternalFailureException("Could not create window.", "Windows", "RegisterClassEx", "DevaFramework::Window::initOSWindow");
	}

	DWORD ex_style = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
	DWORD style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;

	// Create window with the registered class:
	RECT wr = { 0, 0, LONG(this->surface_width), LONG(this->surface_height) };
	AdjustWindowRectEx(&wr, style, FALSE, ex_style);
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

	if (!this->impl_win32_window) {
		throw DevaExternalFailureException("Could not create window.", "Windows", "CreateWindowEx", "DevaFramework::Window::initOSWindow");
	}

	SetWindowLongPtr(impl_win32_window, GWLP_USERDATA, (LONG_PTR)this);

	ShowWindow(this->impl_win32_window, SW_SHOW);
	SetForegroundWindow(this->impl_win32_window);
	SetFocus(this->impl_win32_window);
}

void Window::moveOSWindow(Window &&wnd)
{
	this->impl_win32_class_id_counter = wnd.impl_win32_class_id_counter;
	wnd.impl_win32_class_id_counter = NULL;
	this->impl_win32_class_name = wnd.impl_win32_class_name;
	wnd.impl_win32_class_name = "";
	this->impl_win32_instance = wnd.impl_win32_instance;
	wnd.impl_win32_instance = NULL;
	this->impl_win32_window = wnd.impl_win32_window;
	wnd.impl_win32_window = NULL;
}

void Window::deInitOSWindow()
{
	DestroyWindow(this->impl_win32_window);
	UnregisterClass(this->impl_win32_class_name.c_str(), this->impl_win32_instance);
}

void Window::updateOSWindow()
{
	MSG msg;
	if (PeekMessage(&msg, this->impl_win32_window, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

#endif