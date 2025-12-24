#pragma once

#include "Shroom/Core/Core.h"

namespace Shroom {

    enum class EventType {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased, KeyTyped,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    enum EventCategory {
        None = 0,
        EventCategoryApplication = BIT(0),
        EventCategoryInput = BIT(1),
        EventCategoryKeyboard = BIT(2),
        EventCategoryMouse = BIT(3),
        EventCategoryMouseButton = BIT(4)
    };

    #define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								    virtual EventType GetEventType() const override { return GetStaticType(); }\
								    virtual const char* GetName() const override { return #type; }

    #define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

    class Event {
        friend class EventDispatcher;

    public:
        virtual EventType GetEventType() const = 0;
        virtual const char* GetName() const = 0;
        virtual int GetCategoryFlags() const = 0;
        virtual String ToString() const { return GetName(); }

        inline bool IsInCategory(EventCategory category) const { return GetCategoryFlags() & category; }

        void Handle() { _Handled = true; }
        inline bool IsHandled() const { return _Handled; }

    protected:
        bool _Handled = false;
    };

    class EventDispatcher {
    public:
        EventDispatcher(Event& event) : _Event(event) {}

        template<typename T, typename F>
        bool Dispatch(const F& func) {
            if (_Event.GetEventType() != T::GetStaticType()) return false;

            _Event._Handled = func(static_cast<T&>(_Event));
            return true;
        }

    private:
        Event& _Event;
    };

} // namespace Shroom
