#pragma once
#include "RendererAPI.h"

#include <memory>
class RenderCommand 
{
public:
	static inline void Init() 
	{
		if (!s_RendererAPI)
			s_RendererAPI = std::unique_ptr<RendererAPI>(RendererAPI::Create());
	}
	static inline void Clear() 
	{
		s_RendererAPI->Clear();
	}
	static inline void SetClearColor(float r, float g, float b, float a) 
	{
		s_RendererAPI->SetClearColor(r, g, b, a);
	}
	static inline void SetViewport(float x, float y, float width, float height) 
	{
		s_RendererAPI->SetViewport(x,y, width, height);
	}

	static inline void DrawElements(VertexArray& vao, int count = 0) 
	{
		s_RendererAPI->DrawElements(vao, count);
	}
	static inline void DrawArrays(VertexArray& vao, int count) 
	{
		s_RendererAPI->DrawArrays(vao, count);
	}

private:
	static std::unique_ptr<RendererAPI> s_RendererAPI;
};