#ifndef DEVA_FRAMEWORK_WINDOW_WINDOW_NEW_H
#define DEVA_FRAMEWORK_WINDOW_WINDOW_NEW_H

#include "Config.hpp"

#ifdef DEVA_OS_WIN32
#include <windows.h>
#endif

namespace DevaFramework
{
	class Window
	{
	public:

		struct KeyEventCallback
		{

		};


		DEVA_FRAMEWORK_API static Window& openWindow(uint32_t width, uint32_t height, const std::string &name);

	private:

		Window(uint32_t size_x, uint32_t size_y, const std::string &name);
	public:

		Window(Window &&wnd);
		~Window();

	private:

		void Close();
		bool Update();

		void initOSWindow();
		void deInitOSWindow();
		void updateOSWindow();
		void initOSSurface();
		
		void moveOSWindow(Window &&wnd);

		uint32_t surface_width = 512;
		uint32_t surface_height = 512;
		std::string name;

		bool _window_should_run = true;

#ifdef DEVA_OS_WIN32

		HINSTANCE		impl_win32_instance = NULL;
		HWND			impl_win32_window = NULL;
		std::string		impl_win32_class_name;
		static uint64_t	impl_win32_class_id_counter;
#endif

	};
}

#endif //DEVA_FRAMEWORK_WINDOW_WINDOW_NEW_H