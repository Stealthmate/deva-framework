#ifndef DEVA_FRAMEWORK_WINDOW_WINDOW_NEW_H
#define DEVA_FRAMEWORK_WINDOW_WINDOW_NEW_H

#include "Config.hpp"

#ifdef DEVA_OS_WIN32
#include <windows.h>
#endif

#include "WindowObserver.hpp"

#include <memory>

namespace DevaFramework
{
	class Window
	{
	public:
		DEVA_FRAMEWORK_API static Window& openWindow(uint32_t width, uint32_t height, const std::string &name);
	
	private:

		std::string name;
		uint32_t surface_width;
		uint32_t surface_height;

		bool window_should_run = true;

		std::shared_ptr<WindowObserver> eventObserver;

#ifdef DEVA_OS_WIN32
		friend LRESULT CALLBACK WindowsEventHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		HINSTANCE		impl_win32_instance;
		HWND			impl_win32_window;
		std::string		impl_win32_class_name;
		static uint64_t	impl_win32_class_id_counter;
#endif

		Window(uint32_t size_x, uint32_t size_y, const std::string &name);
		Window(const Window &wnd) = delete;
	public:
		DEVA_FRAMEWORK_API Window(Window &&wnd);
		DEVA_FRAMEWORK_API ~Window();

	private:
		void impl_init();
		void impl_move(Window &&wnd);
		void impl_deInit();
		void impl_update();
		void initOSSurface();

	public:

		DEVA_FRAMEWORK_API bool update();
		DEVA_FRAMEWORK_API void close();

		DEVA_FRAMEWORK_API bool isKeyPressed(Key k);

		DEVA_FRAMEWORK_API WindowObserver& getEventObserver();
		DEVA_FRAMEWORK_API const WindowObserver& getEventObserver() const;
		DEVA_FRAMEWORK_API void setWindowObserver();
	};
}

#endif //DEVA_FRAMEWORK_WINDOW_WINDOW_NEW_H