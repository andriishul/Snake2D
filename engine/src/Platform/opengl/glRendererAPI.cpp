#include "glRendererAPI.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "stdexcept"
#include "core/Window.hpp"
glRendererAPI::glRendererAPI() 
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		throw std::runtime_error("Failed to initialize OPENGL GLAD");
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction	
}

void glRendererAPI::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void glRendererAPI::SetClearColor(float r, float g, float b, float a) const
{
	glClearColor(r,g,b,a);
}

void glRendererAPI::SetViewport(float x, float y, float width, float height) const
{
	glViewport(x,y, width, height);
}

void glRendererAPI::DrawElements(VertexArray& vao, int count) const
{
	vao.Bind();
	count = count ?  count : vao.GetIndexBuffer()->GetCount();
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
	vao.Unbind();
}

void glRendererAPI::DrawArrays(VertexArray& vao, int count) const
{
	vao.Bind();
	glDrawArrays(GL_TRIANGLES, 0, count);
	vao.Unbind();
}
