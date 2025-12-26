#pragma once

#include "Shroom/Core/Log.h"
#include "Shroom/Core/Application.h"

extern Shroom::Application* Shroom::CreateApplication();

int main() {
    Shroom::Log::Init();

    Shroom::Application* app = Shroom::CreateApplication();

    app->Run();

    Shroom::Log::Shutdown();
}
