#include "Shroom/Input/Input.h"

#include "Platform/SDL/SDLInputUtils.h"

namespace Shroom::Input {

    bool IsKeyPressed(KeyCode kcode) {
        SDL_Keycode skcode = Utils::KeyCodeToSDL(kcode);
        const bool* state = SDL_GetKeyboardState(nullptr);
        SDL_Scancode scode = SDL_GetScancodeFromKey(skcode, nullptr);
        return state[scode];
    }

    bool IsMouseButtonPressed(MouseCode mcode) {
        uint8 smcode = Utils::MouseCodeToSDL(mcode);
        SDL_MouseButtonFlags buttons = SDL_GetMouseState(nullptr, nullptr);
        return (buttons & SDL_BUTTON_MASK(smcode)) != 0;
    }
    
    glm::vec2 GetMousePosition() {
        glm::vec2 v = glm::vec2(0.0f);
        SDL_GetMouseState(&v.x, &v.y);
        return v;
    }
    
    float32 GetMouseX() {
        float32 x = 0.0f;
        SDL_GetMouseState(&x, nullptr);
        return x;
    }
    
    float32 GetMouseY() {
        float32 y = 0.0f;
        SDL_GetMouseState(nullptr, &y);
        return y;
    }
    
} // namespace Shroom::Input
