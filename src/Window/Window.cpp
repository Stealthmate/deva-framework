#include "Window.hpp"

#include <GLFW/glfw3.h>
#include <vector>
#include <memory>


using namespace DevaFramework;

static std::vector<Window> opened_windows;

static bool GLFW_READY = false;

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
	if (!GLFW_READY)
	{
		glfwInit();
		GLFW_READY = true;
	}

	opened_windows.push_back(Window(width, height, title, Xpos, Ypos));
	return opened_windows[opened_windows.size() - 1];
}


void DevaFramework::OnWindowShouldClose(Window_Handle hwnd)
{
	for (int i = 0;i <= opened_windows.size() - 1; i++)
	{
		if (opened_windows[i].handle == hwnd)
		{
			opened_windows[i].setShouldClose(true);
			opened_windows[i].close_callback(opened_windows[i]);
		}
	}
}

void Window::setup()
{
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);//For some reason, core profile doesn't draw anything
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	this->handle = glfwCreateWindow(this->width, this->height, this->title.c_str(), nullptr, nullptr);
	this->should_close = false;
	glfwSetWindowCloseCallback(this->handle, OnWindowShouldClose);
	this->close_callback = [](Window &wnd) { wnd.close(); };
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
	should_close(wnd.should_close), close_callback(wnd.close_callback)
{
	this->handle = wnd.handle;
	wnd.handle = WINDOW_HANDLE_NULL;
}

Window & DevaFramework::Window::operator=(Window && wnd)
{
	this->width = wnd.width;
	this->height = wnd.height;
	this->title = wnd.title;
	this->should_close = wnd.should_close;
	this->close_callback = wnd.close_callback;
	if (this->handle) glfwDestroyWindow(this->handle);
	this->handle = wnd.handle;
	wnd.handle = WINDOW_HANDLE_NULL;
	return *this;
}


bool Window::shouldClose()
{
	if (!this->handle) return true;
	this->should_close = glfwWindowShouldClose(this->handle);
	return this->should_close;
}


void Window::setShouldClose(bool flag)
{
	this->should_close = true;
	glfwSetWindowShouldClose(this->handle, this->should_close);
}

void Window::resize(unsigned int width, unsigned int height)
{
	this->width = width;
	this->height = height;
	glfwSetWindowSize(this->handle, this->width, this->height);
}
#include <iostream>
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


