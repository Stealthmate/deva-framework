#include "Window.hpp"

#include <GLFW/glfw3.h>
#include <vector>
#include <memory>

#include "../src/System/Logger.hpp"

using namespace DevaFramework;

static std::vector<Window> opened_windows;

void Window::setCurrentWindow(const Window &wnd)
{
	glfwMakeContextCurrent(wnd.handle);
}

Window& Window::createWindow(
	unsigned int width, 
	unsigned int height, 
	const std::string& title,
	unsigned int Xpos,
	unsigned int Ypos)
{
	opened_windows.push_back(Window(width, height, title, Xpos, Ypos));
	return opened_windows[opened_windows.size() - 1];
}

void Window::setup()
{

	if (!__DEVA_FRAMEWORK_WINDOW_INIT) {
		Logger::println("Deva not initialized! Call DEVA_INIT() BEFORE you use any Deva functions. (GLFW not initialized).");
		this->handle = nullptr;
		return;
	}

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);//For some reason, core profile doesn't draw anything
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	this->handle = glfwCreateWindow(this->width, this->height, this->title.c_str(), nullptr, nullptr);
	this->should_close = false;
	glfwSetWindowCloseCallback(this->handle, OnWindowShouldClose);
	this->close_callback = nullptr;
	glfwSetKeyCallback(handle, OnKeyAction);
	this->key_callback = nullptr;
	glfwSetMouseButtonCallback(handle, OnMouseButtonAction);
	this->mousebutton_callback = nullptr;
}


Window::Window(
	unsigned int width, 
	unsigned int height, 
	const std::string& title,
	unsigned int Xpos,
	unsigned int Ypos)
	: width(width), height(height), title(title), Xpos(Xpos), Ypos(Ypos)
{
	this->setup();
}

Window::Window(Window && wnd)
	: width(wnd.width), height(wnd.height), 
	title(wnd.title), 
	should_close(wnd.should_close), close_callback(wnd.close_callback),
	key_callback(wnd.key_callback), mousebutton_callback(wnd.mousebutton_callback)
{
	this->handle = wnd.handle;
	wnd.handle = WINDOW_HANDLE_NULL;
}

Window& DevaFramework::Window::operator=(Window && wnd)
{
	this->width = wnd.width;
	this->height = wnd.height;
	this->title = wnd.title;
	this->should_close = wnd.should_close;
	this->close_callback = wnd.close_callback;
	this->key_callback = wnd.key_callback;
	this->mousebutton_callback = wnd.mousebutton_callback;
	if (this->handle) glfwDestroyWindow(this->handle);
	this->handle = wnd.handle;
	wnd.handle = WINDOW_HANDLE_NULL;
	return *this;
}

unsigned int Window::getWidth() const
{
	return this->width;
}

unsigned int Window::getHeight() const
{
	return this->height;
}

std::string Window::getTitle() const
{
	return this->title;
}

bool Window::shouldClose()
{
	if (!this->handle) return true;
	this->should_close = glfwWindowShouldClose(this->handle) != 0;
	return this->should_close;
}

void Window::setTitle(const std::string &title)
{
	glfwSetWindowTitle(this->handle, title.c_str());
	this->title = title;
}

void Window::setShouldClose(bool flag)
{
	this->should_close = true;
	glfwSetWindowShouldClose(this->handle, this->should_close);
}

void DevaFramework::OnWindowShouldClose(Window_Handle hwnd)
{
	for (int i = 0;i <= opened_windows.size() - 1;i++)
	{
		if (opened_windows[i].handle == hwnd)
		{
			opened_windows[i].setShouldClose(true);
			if (opened_windows[i].close_callback)
				opened_windows[i].close_callback(opened_windows[i]);
			break;
		}
	}
}


void Window::setCloseCallback(func_WindowCloseCallback close_callback)
{
	this->close_callback = close_callback;
}

bool Window::isKeyDown(Key k) const
{
	return glfwGetKey(this->handle, k) == InputAction::PRESS;
}

bool Window::isMouseButtonDown(MouseButton mb) const
{
	return glfwGetMouseButton(this->handle, mb) == InputAction::PRESS;
}

void DevaFramework::OnKeyAction(Window_Handle hwnd, int key, int scancode, int action, int modmask)
{
	for (int i = 0;i <= opened_windows.size() - 1;i++)
	{
		if (opened_windows[i].handle == hwnd)
		{
			if (opened_windows[i].key_callback) 
				opened_windows[i].key_callback(
					opened_windows[i], static_cast<Key>(key), static_cast<InputAction>(action), modmask);
			break;
		}
	}
}

void Window::setOnKeyActionCallback(func_OnKeyAction cb)
{
	this->key_callback = cb;
}

void DevaFramework::OnMouseButtonAction(Window_Handle hwnd, int mousebutton, int action, int modmask)
{
	for (int i = 0;i <= opened_windows.size() - 1;i++)
	{
		if (opened_windows[i].handle == hwnd)
		{
			if (opened_windows[i].mousebutton_callback)
				opened_windows[i].mousebutton_callback(
					opened_windows[i], static_cast<MouseButton>(mousebutton), static_cast<InputAction>(action), modmask);
			break;
		}
	}
}

void Window::setOnMouseButtonActionCallback(func_OnMouseButtonAction cb)
{
	this->mousebutton_callback = cb;
}

void Window::resize(unsigned int width, unsigned int height)
{
	this->width = width;
	this->height = height;
	glfwSetWindowSize(this->handle, this->width, this->height);
}

void Window::move(unsigned int topleft_X, unsigned int topleft_Y)
{
	glfwSetWindowPos(this->handle, topleft_X, topleft_Y);
	this->Xpos = topleft_X;
	this->Ypos = topleft_Y;
}

void Window::update()
{
	if (!this->handle) return;
	glfwSwapBuffers(this->handle);
	glfwPollEvents();
}

void Window::close()
{
	if (this->handle)
	{
		glfwSetWindowShouldClose(this->handle, true);
		glfwDestroyWindow(this->handle);
		this->handle = WINDOW_HANDLE_NULL;
	}
}

Window::~Window()
{
	if (this->handle) this->close();
}


