#pragma once

#include "Shroom/Events/Event.h"

// TODO: Refactor to use Shroom::string
#include <sstream>

namespace Shroom {

    class WindowCloseEvent : public Event {
    public:
        WindowCloseEvent() {}

        EVENT_CLASS_TYPE(WindowClose)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class WindowResizeEvent : public Event {
    public:
        WindowResizeEvent(uint32 width, uint32 height) : _Width(width), _Height(height) {}

        inline uint32 GetWidth() const { return _Width; }
        inline uint32 GetHeight() const { return _Height; }

        String ToString() const override {
            std::stringstream ss;
            ss << "WindowResizeEvent: " << _Width << ", " << _Height;
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowResize)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)

    private:
        uint32 _Width;
        uint32 _Height;
    };

    class WindowFocusEvent : public Event {
    public:
        WindowFocusEvent() {}

        EVENT_CLASS_TYPE(WindowFocus)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class WindowLostFocusEvent : public Event {
    public:
        WindowLostFocusEvent() {}

        EVENT_CLASS_TYPE(WindowLostFocus)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class WindowMovedEvent : public Event {
    public:
        WindowMovedEvent(int32 x, int32 y) : _X(x), _Y(y) {}
        
        int32 GetX() const { return _X; }
        int32 GetY() const { return _Y; }

		String ToString() const override {
			std::stringstream ss;
			ss << "WindowMovedEvent: " << _X << ", " << _Y;
			return ss.str();
		}

        EVENT_CLASS_TYPE(WindowMoved)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)

    private:
        int32 _X, _Y;
    };

    class AppTickEvent : public Event {
    public:
        AppTickEvent() {}

        EVENT_CLASS_TYPE(AppTick)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class AppUpdateEvent : public Event {
    public:
        AppUpdateEvent() {}

        EVENT_CLASS_TYPE(AppUpdate)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class AppRenderEvent : public Event {
    public:
        AppRenderEvent() {}

        EVENT_CLASS_TYPE(AppRender)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

} // namespace Shroom