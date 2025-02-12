#include "glfwWindow.hpp"
#include <stdexcept>
#include <string>
#include "glfw/glfw3.h"

#include <Event/KeyEvent.hpp>
#include <Event/MouseEvent.hpp>
#include <Event/WindowEvent.hpp>

#include <Image.hpp>
int glfwWindow::s_WindowCount = 0;

void glfwWindow::OnError(int error_code, const char* description)
{
	std::string msg = "Description: " + std::string(description)
		+ "\nError_code: " + std::to_string(error_code);
	throw std::runtime_error(msg);
}
void glfwWindow::Init(const char* title, const glm::ivec2& size)
{
	glfwSetErrorCallback(glfwWindow::OnError);
	if (s_WindowCount == 0) 
		glfwInit();
	
	m_data.m_Handle = glfwCreateWindow(size.x, size.y, title, nullptr, nullptr);
	glfwMakeContextCurrent(static_cast<GLFWwindow*>(m_data.m_Handle));
	
	glfwSetWindowUserPointer(static_cast<GLFWwindow*>(m_data.m_Handle), &m_data);
	glfwSetKeyCallback(static_cast<GLFWwindow*>(m_data.m_Handle), [](GLFWwindow* window,
		int key, int scancode, int action, int mods)
		{
			if (action == GLFW_PRESS) 
			{
				KeyPressedEvent keyPressed = (KeyCode)key;
				WindowInfo& info = *(WindowInfo*)glfwGetWindowUserPointer(window);
				if (info.m_Callback)
					info.m_Callback(keyPressed);
			}
			else if (action == GLFW_REPEAT)
			{
				KeyPressedEvent keyRepeated = { (KeyCode)key, true };
				WindowInfo& info = *(WindowInfo*)glfwGetWindowUserPointer(window);
				if (info.m_Callback)
					info.m_Callback(keyRepeated);
			}
			else if (action == GLFW_RELEASE) {
				KeyReleasedEvent keyReleased = (KeyCode)key;
				WindowInfo& info = *(WindowInfo*)glfwGetWindowUserPointer(window);
				if (info.m_Callback)
					info.m_Callback(keyReleased);
			}
		});
	glfwSetCharCallback(static_cast<GLFWwindow*>(m_data.m_Handle), [](GLFWwindow* window, unsigned ch)
		{
			KeyTypedEvent keyTyped = ch;
			WindowInfo& info = *(WindowInfo*)glfwGetWindowUserPointer(window);
			if (info.m_Callback)
				info.m_Callback(keyTyped);
		});
	glfwSetMouseButtonCallback(static_cast<GLFWwindow*>(m_data.m_Handle), [](GLFWwindow* window, int button, int action, int mods)
		{
			if (action == GLFW_PRESS) {
				MouseButtonPressedEvent mouseButtonPressed = (MouseButton)button;
				WindowInfo& info = *(WindowInfo*)glfwGetWindowUserPointer(window);
				if (info.m_Callback)
					info.m_Callback(mouseButtonPressed);
			}
			else if (action == GLFW_RELEASE) 
			{
				MouseButtonReleasedEvent mouseButtonReleased = (MouseButton)button;
				WindowInfo& info = *(WindowInfo*)glfwGetWindowUserPointer(window);
				if (info.m_Callback)
					info.m_Callback(mouseButtonReleased);
			}
		});
	glfwSetCursorPosCallback(static_cast<GLFWwindow*>(m_data.m_Handle), [](GLFWwindow* window, double xpos, double ypos)
		{
			MouseMovedEvent mouseMoved = {	static_cast<float>(xpos), static_cast<float>(ypos) };
			WindowInfo& info = *(WindowInfo*)glfwGetWindowUserPointer(window);
			if (info.m_Callback)
				info.m_Callback(mouseMoved);
		});
	glfwSetWindowSizeCallback(static_cast<GLFWwindow*>(m_data.m_Handle), [](GLFWwindow* window, int width, int height)
		{
			WindowResizedEvent windowResized = {	width,	height	};
			WindowInfo& info = *(WindowInfo*)glfwGetWindowUserPointer(window);
			if (info.m_Callback)
				info.m_Callback(windowResized);
		});
	glfwSetWindowCloseCallback(static_cast<GLFWwindow*>(m_data.m_Handle), [](GLFWwindow* window)
		{
			WindowCloseEvent windowClose;
			WindowInfo& info = *(WindowInfo*)glfwGetWindowUserPointer(window);
			if (info.m_Callback)
				info.m_Callback(windowClose);
		});  
	s_WindowCount++;
	//SetVSync(true);
}
glfwWindow::glfwWindow(const std::string& title, const glm::ivec2& size) 
{
	Init(title.c_str(), size);
}

glfwWindow::~glfwWindow()
{
	glfwDestroyWindow(static_cast<GLFWwindow*>(m_data.m_Handle));
	s_WindowCount--;
	if (s_WindowCount == 0) 
		glfwTerminate();
}

void glfwWindow::SetTitle(const std::string title)
{
	glfwSetWindowTitle(static_cast<GLFWwindow*>(m_data.m_Handle), title.c_str());
}

void glfwWindow::SetSize(const glm::ivec2& size)
{
	glfwSetWindowSize(static_cast<GLFWwindow*>(m_data.m_Handle), size.x, size.y);
}

glm::ivec2 glfwWindow::GetSize() const
{
	glm::ivec2 size;
	glfwGetWindowSize(static_cast<GLFWwindow*>(m_data.m_Handle),&size.x,&size.y);
	return size;
}

void glfwWindow::SetVSync(bool enable)
{
	int interval = enable ? 1 : 0;
	glfwSwapInterval(interval);
	m_data.m_IsVSync = enable;
}
void glfwWindow::SetIcon(const std::string& iconFile)
{
	int channels = 0;
	Image image(iconFile.c_str());
	GLFWimage glfw_image;
	glfw_image.pixels = image.GetPixels();
	glfw_image.height = image.GetHeight();
	glfw_image.width = image.GetWidth();
	glfwSetWindowIcon(static_cast<GLFWwindow*>(m_data.m_Handle), 1, &glfw_image);
}
void glfwWindow::OnUpdate() const
{
	glfwSwapBuffers(static_cast<GLFWwindow*>(m_data.m_Handle));
	glfwPollEvents();
}

