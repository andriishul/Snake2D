#include "Input.h"
#include "gApplication.hpp"
#include "glfw/glfw3.h"

bool Input::IsKeyPressed(KeyCode key) 
{
	const Window& currentWindow = gApplication::GetInstance().GetWindow();
	GLFWwindow* window = (GLFWwindow*)currentWindow.GetNativeWindow();
	return glfwGetKey(window, static_cast<int>(key)) == GLFW_PRESS; 
}

bool Input::IsKeyReleased(KeyCode key)
{
	const Window& currentWindow = gApplication::GetInstance().GetWindow();
	GLFWwindow* window = (GLFWwindow*)currentWindow.GetNativeWindow();
	return glfwGetKey(window, static_cast<int>(key)) == GLFW_RELEASE;
}