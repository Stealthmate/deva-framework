#ifndef DEVA_FRAMEWORK_WINDOW_IMPL_WINDOW_HPP
#define DEVA_FRAMEWORK_WINDOW_IMPL_WINDOW_HPP

#include "Config.hpp"
#include "Window.hpp"

#ifdef DEVA_OS_WIN32
#include <windows.h>
#endif

namespace DevaFramework
{
	class Window::ImplWindow
	{
		std::string name;
		uint32_t surface_width;
		uint32_t surface_height;

		bool window_should_run = true;

		std::shared_ptr<WindowObserver> eventObserver;

	public:
		ImplWindow(Window &wnd, uint32_t size_x, uint32_t size_y, const std::string &name);
		ImplWindow(const ImplWindow &implwnd) = delete;
		ImplWindow& operator=(const ImplWindow &wnd) = delete;
		ImplWindow(ImplWindow &&implwnd);
		~ImplWindow();
	private:

#ifdef DEVA_OS_WIN32
		friend LRESULT CALLBACK WindowsEventHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		HINSTANCE		impl_win32_instance;
		HWND			impl_win32_window;
		std::string		impl_win32_class_name;
		static uint64_t	impl_win32_class_id_counter;
#endif

	private:
		void impl_init();
		void impl_move(ImplWindow &&wnd);
		void impl_deInit();
		void impl_update();
		void initOSSurface();
	public:
		bool update();
		void close();

		WindowObserver& getEventObserver();
		const WindowObserver& getEventObserver() const;
		void setWindowObserver();
	};
}

#endif //DEVA_FRAMEWORK_WINDOW_IMPL_WINDOW_HPP