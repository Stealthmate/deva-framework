#ifndef DEVA_FRAMEWORK_WINDOW_WINDOW_NEW_H
#define DEVA_FRAMEWORK_WINDOW_WINDOW_NEW_H

#include "Config.hpp"

#include "WindowObserver.hpp"

namespace DevaFramework
{
	struct OSHandles
	{
		DEVA_FRAMEWORK_API virtual void* win32_hinstance() const;
		DEVA_FRAMEWORK_API virtual void* win32_hwnd() const;

		DEVA_FRAMEWORK_API virtual void* xcb_connection() const;
		DEVA_FRAMEWORK_API virtual void* xcb_window() const;

		DEVA_FRAMEWORK_API virtual void* xlib_dpy() const;
		DEVA_FRAMEWORK_API virtual void* xlib_window() const;
	};

	class Window
	{
		friend class Surface;

	public:
		class ImplWindow;

	private:
		std::unique_ptr<ImplWindow> impl;

		Window(uint32_t size_x, uint32_t size_y, const std::string &name);

	public:
		DEVA_FRAMEWORK_API static std::shared_ptr<Window> openWindow(uint32_t width, uint32_t height, const std::string &name);
	
		Window(const Window &wnd) = delete;
		DEVA_FRAMEWORK_API Window(Window &&wnd);
		Window& operator=(const Window &wnd) = delete;
		DEVA_FRAMEWORK_API Window& operator=(Window &&wnd);
		DEVA_FRAMEWORK_API ~Window();

		DEVA_FRAMEWORK_API bool update();
		DEVA_FRAMEWORK_API void close();

		DEVA_FRAMEWORK_API WindowObserver& getEventObserver();
		DEVA_FRAMEWORK_API const WindowObserver& getEventObserver() const;
		DEVA_FRAMEWORK_API void setWindowObserver();

		DEVA_FRAMEWORK_API void* getUserData() const;
		DEVA_FRAMEWORK_API void setUserData(void* data);

		DEVA_FRAMEWORK_API std::unique_ptr<OSHandles> getOSHandles() const;

		DEVA_FRAMEWORK_API unsigned int getWidth() const;
		DEVA_FRAMEWORK_API unsigned int getHeight() const;
	};
}

#endif //DEVA_FRAMEWORK_WINDOW_WINDOW_NEW_H