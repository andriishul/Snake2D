#pragma once
#include "Event.hpp"
#include <Core/MouseCodes.hpp>

class MouseButtonPressedEvent : public Event
{
public:
	MouseButtonPressedEvent(MouseButton button) :
		m_Button(button) {}
	virtual operator std::string() const override
	{
		std::string buttonName;
		switch (m_Button)
		{
		case MouseButton::Left:
			buttonName = "Left mouse button";
			break;
		case MouseButton::Right:
			buttonName = "Right mouse button";
			break;
		case MouseButton::Middle:
			buttonName = "Middle mouse button";
			break;
		default:
			break;
		}
		return std::string("MouseButtonPressedEvent: ") + buttonName;
	}
	MouseButton GetButton() const { return m_Button; }
	EVENT_CLASS_TYPE(MouseButtonPressed)
private:
	MouseButton m_Button;
};

class MouseButtonReleasedEvent : public Event
{
public:
	MouseButtonReleasedEvent(MouseButton button) :
		m_Button(button) {}
	virtual operator std::string() const override 
	{
		std::string buttonName;
		switch (m_Button)
		{
		case MouseButton::Left:
			buttonName = "Left mouse button";
			break;
		case MouseButton::Right:
			buttonName = "Right mouse button";
			break;
		case MouseButton::Middle:
			buttonName = "Middle mouse button";
			break;
		default:
			break;
		}
		return std::string("MouseButtonReleasedEvent: ") + buttonName;
	}
	MouseButton GetButton() const { return m_Button; }
	EVENT_CLASS_TYPE(MouseButtonReleased)
private:
	MouseButton m_Button;
}; 

class MouseMovedEvent : public Event
{
public:
	MouseMovedEvent(float x, float y) : m_PosX(x), m_PosY(y){}
	virtual operator std::string() const override
	{
		return std::string("MouseMovedEvent: X=") + std::to_string(m_PosX) + " Y=" + std::to_string(m_PosY);
	}
	float GetPosX() const { return m_PosX; }
	float GetPosY() const { return m_PosY; }
	EVENT_CLASS_TYPE(MouseMoved)
private:
	float m_PosX, m_PosY;
};