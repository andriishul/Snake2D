#pragma once
#include "Event.hpp"
#include <Core/KeyCodes.hpp>

class KeyPressedEvent : public Event
{
public:
	KeyPressedEvent(KeyCode key, bool repeat = false) :
		m_Key(key), m_Repeat(repeat) {}
	virtual operator std::string() const override { return std::string("KeyPressedEvent: ") + (char)m_Key; }
	KeyCode GetKey() const { return m_Key; }
	bool Repeat() const { return m_Repeat; }
	EVENT_CLASS_TYPE(KeyPressed)
private:
	KeyCode m_Key;
	bool m_Repeat;
};

class KeyReleasedEvent : public Event
{
public:
	KeyReleasedEvent(KeyCode key) :
		m_Key(key) {}
	KeyCode GetKey() const { return m_Key; }
	virtual operator std::string() const override { return std::string("KeyReleasedEvent: ") + (char)m_Key; }
	EVENT_CLASS_TYPE(KeyReleased)
private:
	KeyCode m_Key;
};

class KeyTypedEvent : public Event
{
public:
	KeyTypedEvent(char c) : m_Character(c) {}
	char GetChar() const { return m_Character; }
	virtual operator std::string() const override { return std::string("KeyTypedEvent: ") + (char)m_Character; }
	EVENT_CLASS_TYPE(KeyTyped)
private:
	char m_Character;
};