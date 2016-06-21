#ifndef DEVA_FRAMEWORK_WINDOW_WINDOW_NEW_H
#define DEVA_FRAMEWORK_WINDOW_WINDOW_NEW_H

#include "Config.hpp"

#include "WindowObserver.hpp"

#include <memory>

namespace DevaFramework
{

	class Window
	{
	public:
		class ImplWindow;
	private:
		std::unique_ptr<ImplWindow> impl;

		DEVA_FRAMEWORK_API Window(uint32_t size_x, uint32_t size_y, const std::string &name);
	public:
		DEVA_FRAMEWORK_API static Window& openWindow(uint32_t width, uint32_t height, const std::string &name);
	
		Window(const Window &wnd) = delete;
		DEVA_FRAMEWORK_API Window(Window &&wnd);

		DEVA_FRAMEWORK_API bool update();
		DEVA_FRAMEWORK_API void close();

		DEVA_FRAMEWORK_API WindowObserver& getEventObserver();
		DEVA_FRAMEWORK_API const WindowObserver& getEventObserver() const;
		DEVA_FRAMEWORK_API void setWindowObserver();
	};
}

#endif //DEVA_FRAMEWORK_WINDOW_WINDOW_NEW_H