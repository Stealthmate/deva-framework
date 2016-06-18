#include "../Window.hpp"

#ifndef DEVA_OS_WIN32
#error "Platform not supported."
#else

#include "../../System/Exceptions.hpp"

#include "../../System/DevaLogger.hpp"

#include "impl_keycode_mapping.inl"

#include <map>
#include <memory>

using namespace DevaFramework;


namespace
{

	std::map<HWND, Window*>  hwnd_map;

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

	std::shared_ptr<WindowEventStruct_KeyEvent> createWindowEventInfo_Key(WindowEvent evt, WPARAM keycode, LPARAM options)
	{
		std::shared_ptr<WindowEventStruct_KeyEvent> infostruct = std::shared_ptr<WindowEventStruct_KeyEvent>(new WindowEventStruct_KeyEvent);
		infostruct->evt = evt;
		Key k = Key::KEY_UNKNOWN;
		auto i = SUPPORTED_KEYS.find(keycode);
		if (i != SUPPORTED_KEYS.end()) k = i->second;
		infostruct->key = k;

		if (infostruct->key == Key::KEY_UNKNOWN) return std::move(infostruct);

		infostruct->scancode = (reinterpret_cast<int8_t*>(&options)[2] & 0xF0);
		infostruct->wasPressed = (reinterpret_cast<int8_t*>(&options)[3] & 0b01000000) != 0;

		return std::move(infostruct);
	}
}

LRESULT CALLBACK DevaFramework::WindowsEventHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (init_call) return DefWindowProc(hWnd, uMsg, wParam, lParam);
	Window &current_wnd = *reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

	switch (uMsg) {
	case WM_CLOSE:
		//window->sendCloseMsg();
		current_wnd.window_should_run = false;
		return 0;
	case WM_SIZE:
		// we get here if the window has changed size, we should rebuild most
		// of our window resources before rendering to this window again.
		// ( no need for this because our window sizing by hand is disabled )
		break;
	case WM_KEYUP:
	{
		current_wnd.eventObserver->fire(current_wnd, std::move(createWindowEventInfo_Key(WindowEvent::EVENT_KEY_UP, wParam, lParam)));
	}
	case WM_KEYDOWN:
	{
		DevaLogger::log << "Keycode " << wParam;
		current_wnd.eventObserver->fire(current_wnd, std::move(createWindowEventInfo_Key(WindowEvent::EVENT_KEY_DOWN, wParam, lParam)));
	}
	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

uint64_t Window::impl_win32_class_id_counter = 0;

void Window::impl_init()
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
	win_class.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
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
		throw DevaExternalFailureException("Could not create window.", "Windows", "CreateWindowEx", "DevaFramework::Window::initOSWindow");
	}

	hwnd_map.insert({this->impl_win32_window, this});

	SetWindowLongPtr(this->impl_win32_window, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

	ShowWindow(this->impl_win32_window, SW_SHOW);
	SetForegroundWindow(this->impl_win32_window);
	SetFocus(this->impl_win32_window);
}

void Window::impl_move(Window &&wnd)
{
	this->impl_win32_class_id_counter = wnd.impl_win32_class_id_counter;
	wnd.impl_win32_class_id_counter = NULL;
	this->impl_win32_class_name = wnd.impl_win32_class_name;
	wnd.impl_win32_class_name = "";
	this->impl_win32_instance = wnd.impl_win32_instance;
	wnd.impl_win32_instance = NULL;
	this->impl_win32_window = wnd.impl_win32_window;
	wnd.impl_win32_window = NULL;

	SetWindowLongPtr(this->impl_win32_window, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
}

void Window::impl_deInit()
{
	DestroyWindow(this->impl_win32_window);
	UnregisterClass(this->impl_win32_class_name.c_str(), this->impl_win32_instance);
}

void Window::impl_update()
{
	if (ex.second) downcastExAndThrow(ex);

	MSG msg;
	if (PeekMessage(&msg, this->impl_win32_window, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

#endif