#pragma once

#include "Shroom/Events/Event.h"

// TODO: Refactor to use Shroom::string
#include <sstream>

namespace Shroom {

    class MouseMovedEvent : public Event {
    public:
        MouseMovedEvent(float32 x, float32 y) : _X(x), _Y(y) {}

        inline float32 GetX() const { return _X; }
        inline float32 GetY() const { return _Y; }

        String ToString() const override {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << _X << ", " << _Y;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseMoved)
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    private:
        float32 _X;
        float32 _Y;
    };

    class MouseScrolledEvent : public Event {
    public:
        MouseScrolledEvent(float32 xOffset, float32 yOffset) : _XOffset(xOffset), _YOffset(yOffset) {}

        inline float32 GetXOffset() const { return _XOffset; }
        inline float32 GetYOffset() const { return _YOffset; }

        String ToString() const override {
            std::stringstream ss;
            ss << "MouseScrolledEvent: " << _XOffset << ", " << _YOffset;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseScrolled)
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    private:
        float32 _XOffset;
        float32 _YOffset;
    };

    class MouseButtonEvent : public Event {
    public:
        inline int32 GetMouseButton() const { return _Button; }

        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    protected:
        MouseButtonEvent(int32 button) : _Button(button) {}

        int32 _Button;
    };

    class MouseButtonPressedEvent : public MouseButtonEvent {
    public:
        MouseButtonPressedEvent(int32 button) : MouseButtonEvent(button) {}

        String ToString() const override {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << _Button;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonPressed)
    };

    class MouseButtonReleasedEvent : public MouseButtonEvent {
    public:
        MouseButtonReleasedEvent(int32 button) : MouseButtonEvent(button) {}

        String ToString() const override {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << _Button;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonReleased)
    };

} // namespace Shroom