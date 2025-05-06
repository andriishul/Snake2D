#pragma once
#include <string>
#include <functional>
#include <vector>
#include <map>

#define BIND_FUNCTION(func,instance) std::bind(&func, instance, std::placeholders::_1)

enum class EventType {
    WindowClose,
    WindowResized,
    KeyTyped,
    KeyPressed,
    KeyReleased,
    MouseButtonPressed,
    MouseButtonReleased,
    MouseMoved
};
#define EVENT_CLASS_TYPE(type) \
    static EventType GetStaticType() { return EventType::type; } \
             virtual EventType GetType() const override { return GetStaticType(); }
class Event       
{
public:
    virtual ~Event() = default;
    virtual EventType GetType() const = 0;
    virtual operator std::string() const { return ""; }
private:
};
template<typename TEvent = Event>
using EventFnCallback = std::function<void(const TEvent&)>;

class EventDispatcher 
{
public:
    EventDispatcher(const Event& event) 
        : m_Event(event) {}
    template<typename t>
    void Invoke(EventFnCallback<t> fn) 
    {
        if (t::GetStaticType() == m_Event.GetType())
            fn((const t&)m_Event);
    }
private:
    const Event& m_Event;
};