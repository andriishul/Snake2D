#pragma once
#include "Buffer.hpp"

#include <string>

class RendererAPI 
{
public:
	virtual ~RendererAPI() = default;

	virtual void Clear() const = 0;
	virtual void SetClearColor(float r, float g, float b, float a) const = 0;
	virtual void SetViewport(float x, float y, float width, float height) const = 0;

	virtual void DrawElements(VertexArray& vao, int count) const = 0;
	virtual void DrawArrays(VertexArray& vao, int count) const = 0;

	virtual std::string GetName() const = 0;

	static RendererAPI* Create();
};