#ifndef DEVA_FRAMEWORK_GRAPHICS_WINDOW_WINDOW_H
#define DEVA_FRAMEWORK_GRAPHICS_WINDOW_WINDOW_H

#include <string>

#include "Config.hpp"

namespace DevaFramework
{
	void OnKeyAction(Window_Handle, int, int, int, int);
	void OnMouseButtonAction(Window_Handle, int, int, int);
	void OnWindowShouldClose(Window_Handle);

	/**
	 @brief A Window to be used for displaying stuff on the screen.
	*/
	class Window
	{
	public:

		/**
		A function which can be set as a callback for when the window should be closed.
		@param wnd The Window that should be closed
		*/
		typedef void(*func_WindowCloseCallback)(Window& wnd);

		typedef void (*func_OnKeyAction)(Window&, Key, InputAction, int modmask);
		typedef void (*func_OnMouseButtonAction)(Window&, MouseButton, InputAction, int modmask);

	private:
		///Default Xpos
		static const unsigned int DEFAULT_XPOS = 0;
		///Default Ypos
		static const unsigned int DEFAULT_YPOS = 0;

		friend void OnWindowShouldClose(Window_Handle);
		friend void OnMouseButtonAction(Window_Handle, int, int, int);
		friend void OnKeyAction(Window_Handle, int, int, int, int);

	public:

		///Set the context, routing all draw calls to the specified window
		static DEVA_WINDOW_API void setCurrentWindow(const Window &wnd);
		///Create a Window with the given parameters
		static DEVA_WINDOW_API Window& createWindow(
			unsigned int width, 
			unsigned int height, 
			const std::string& title, 
			unsigned int Xpos = DEFAULT_XPOS, 
			unsigned int Ypos = DEFAULT_YPOS);

	private:

		///An underlying handle for the window
		Window_Handle handle;
		///The width of the window
		unsigned int width;
		///The height of the window
		unsigned int height;
		///The X coordinate of the top left corner of the window
		unsigned int Xpos;
		///The Y coordinate of the top left corner of the window
		unsigned int Ypos;
		///The title of the window
		std::string title;
		///True if the window has received a close event, false otherwise
		bool should_close;

		///The function to be called when the window receives a close event
		func_WindowCloseCallback close_callback;
		func_OnKeyAction key_callback;
		func_OnMouseButtonAction mousebutton_callback;

		///Constructs a window with the specified parameters
		Window(
			unsigned int width,
			unsigned int height,
			const std::string& title,
			unsigned int Xpos = DEFAULT_XPOS,
			unsigned int Ypos = DEFAULT_YPOS);

		Window(const Window &wnd) = delete;
		Window& operator=(const Window &wnd) = delete;

		void setup();

	public:
		///Transfers ownership of the window from wnd
		DEVA_WINDOW_API Window(Window &&wnd);
		///Destroys the current window and transfers ownership from wnd
		DEVA_WINDOW_API Window& operator=(Window &&wnd);

		DEVA_WINDOW_API unsigned int getWidth() const;
		DEVA_WINDOW_API unsigned int getHeight() const;
		DEVA_WINDOW_API std::string getTitle() const;
		DEVA_WINDOW_API bool shouldClose();

		DEVA_WINDOW_API void setTitle(const std::string &title);
		DEVA_WINDOW_API void setShouldClose(bool flag);
		DEVA_WINDOW_API void setCloseCallback(func_WindowCloseCallback close_callback);

		DEVA_WINDOW_API bool isKeyDown(Key k) const;
		DEVA_WINDOW_API bool isMouseButtonDown(MouseButton mb) const;
		DEVA_WINDOW_API void setOnKeyActionCallback(func_OnKeyAction cb);
		DEVA_WINDOW_API void setOnMouseButtonActionCallback(func_OnMouseButtonAction cb);

		///Resizes the window to the specified dimensions
		DEVA_WINDOW_API void resize(unsigned int width, unsigned int height);
		///Moves the top left corner of the window to the specified position
		DEVA_WINDOW_API void move(unsigned int x, unsigned int y);

		///Swaps the buffers and updates the event queue
		DEVA_WINDOW_API void update();
		///Marks the window closed and destroys it, releasing any resources associated with it in the process
		DEVA_WINDOW_API void close();

		///Calls close() if the window is still open
		DEVA_WINDOW_API ~Window();
	};

}

#endif // DEVA_FRAMEWORK_GRAPHICS_WINDOW_WINDOW_H
