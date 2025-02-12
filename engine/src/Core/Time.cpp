#include "Time.hpp"
#include "GLFW/glfw3.h"
double Time::Get()
{
	return glfwGetTime();
}
