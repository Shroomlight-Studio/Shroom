#pragma once

#include "Shroom/Events/Event.h"

// TODO: Refactor to use Shroom::string
#include <sstream>

namespace Shroom {

    class KeyEvent : public Event {
    public:
        inline int32 GetKeyCode() const { return _Keycode; }

        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

    protected:
        KeyEvent(int32 keycode) : _Keycode(keycode) {}

        int32 _Keycode;
    };

    class KeyPressedEvent : public KeyEvent {
    public:
        KeyPressedEvent(int32 keycode, bool isRepeat = false) : KeyEvent(keycode), _IsRepeat(isRepeat) {}

        inline bool IsRepeat() const { return _IsRepeat; }

        String ToString() const override {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << _Keycode << " (repeats = " << _IsRepeat << ")";
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPressed)

    private:
        bool _IsRepeat;
    };

    class KeyReleasedEvent : public KeyEvent {
    public:
        KeyReleasedEvent(int32 keycode) : KeyEvent(keycode) {}

        String ToString() const override {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << _Keycode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyReleased)
    };

    class KeyTypedEvent : public KeyEvent {
    public:
        KeyTypedEvent(int32 keycode) : KeyEvent(keycode) {}

        String ToString() const override {
            std::stringstream ss;
            ss << "KeyTypedEvent: " << _Keycode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyTyped)
    };

} // namespace Shroom