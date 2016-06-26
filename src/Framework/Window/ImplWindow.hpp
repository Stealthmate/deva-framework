#ifndef DEVA_FRAMEWORK_WINDOW_IMPL_WINDOW_HPP
#define DEVA_FRAMEWORK_WINDOW_IMPL_WINDOW_HPP

#include "Config.hpp"
#include "Window.hpp"

#include <map>

#ifdef DEVA_OS_WIN32
#include <windows.h>
#endif

namespace DevaFramework
{
	class Window::ImplWindow
	{
#ifdef DEVA_OS_WIN32
		friend LRESULT CALLBACK WindowsEventHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		HINSTANCE		impl_win32_instance;
		HWND			impl_win32_window;
		std::string		impl_win32_class_name;
		static uint64_t	impl_win32_class_id_counter;
		typedef HANDLE DeviceHandle;
#endif
		friend class Window;

		Window * wnd;

		std::string name;
		uint32_t surface_width;
		uint32_t surface_height;

		bool window_should_run = true;

		std::shared_ptr<WindowObserver> eventObserver;

		void* userData;


		void impl_init();
		void impl_move(ImplWindow &&wnd);
		void impl_deInit();
		void impl_update();
		void initOSSurface();

	public:
		ImplWindow(Window *wnd, uint32_t size_x, uint32_t size_y, const std::string &name);
		ImplWindow(const ImplWindow &implwnd) = delete;
		ImplWindow& operator=(const ImplWindow &wnd) = delete;
		ImplWindow(ImplWindow &&implwnd) = delete;
		ImplWindow& operator=(ImplWindow &&wnd) = default;
		ImplWindow(ImplWindow &&implwnd, Window* new_wnd);
		~ImplWindow();

		bool update();
		void close();

		WindowObserver& getEventObserver();
		const WindowObserver& getEventObserver() const;
		void setWindowObserver();

		void* getUserData() const;
		void setUserData(void *userData);
	};
}

#endif //DEVA_FRAMEWORK_WINDOW_IMPL_WINDOW_HPP