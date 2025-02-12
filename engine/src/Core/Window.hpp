#pragma once
#include "Event/WindowEvent.hpp"
#include <glm/vec2.hpp>

struct WindowOptions {
	std::string Title;
	glm::ivec2 Size;
};

class Window 
{
public:
	virtual ~Window() = default;
	
	virtual void SetTitle(const std::string title) = 0;
	virtual void SetSize(const glm::ivec2&) = 0;
	virtual glm::ivec2 GetSize() const = 0;
	
	virtual void SetVSync(bool) = 0;
	virtual bool IsVSync() const = 0;
	
	virtual void SetIcon(const std::string& iconFile) = 0;

	virtual void SetEventCallback(const EventFnCallback<> &eventFn) = 0;

	virtual void OnUpdate() const = 0;

	virtual void* GetNativeWindow() const = 0;

	static Window* Create(WindowOptions options);
};
