#pragma once

#include "Shroom/Input/KeyCode.h"
#include "Shroom/Input/MouseCode.h"

#include <glm/glm.hpp>

namespace Shroom::Input {
    
    static bool IsKeyPressed(KeyCode kcode);

    static bool IsMouseButtonPressed(MouseCode mcode);
    static glm::vec2 GetMousePosition();
    static float32 GetMouseX();
    static float32 GetMouseY();

} // namespace Shroom::Input

