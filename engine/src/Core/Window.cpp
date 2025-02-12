#include "Window.hpp"
#include <platform/glfw/glfwWindow.hpp>

Window* Window::Create(WindowOptions options)
{
	return new glfwWindow(options.Title, options.Size);
}