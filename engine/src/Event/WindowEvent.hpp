#pragma once
#include "Event.hpp"

class WindowResizedEvent : public Event
{
public:
	WindowResizedEvent(int width, int height) : m_Width(width), m_Height(height)
	{}
	int GetWidth() const { return m_Width; }
	int GetHeight() const { return m_Height; }
	virtual operator std::string() const override { return "WindowResizedEvent: width=" + std::to_string(GetWidth()) + " height=" + std::to_string(GetHeight()); }
	EVENT_CLASS_TYPE(WindowResized)
private:
	int m_Width, m_Height;
};

class WindowCloseEvent : public Event
{
public:
	WindowCloseEvent() = default;
	EVENT_CLASS_TYPE(WindowClose)
};