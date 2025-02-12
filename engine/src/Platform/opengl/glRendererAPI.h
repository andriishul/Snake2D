#pragma once
#include <Graphics/RendererAPI.h>

class glRendererAPI : public RendererAPI
{
public:
	glRendererAPI();

	virtual void Clear() const override;
	virtual void SetClearColor(float r, float g, float b, float a) const override;
	virtual void SetViewport(float x, float y, float width, float height) const override;

	virtual void DrawElements(VertexArray& vao, int count) const override;
	virtual void DrawArrays(VertexArray& vao, int count) const override;

	virtual std::string GetName() const override { return "OPENGL"; }
};