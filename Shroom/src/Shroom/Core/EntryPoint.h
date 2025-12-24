#pragma once

#include "Shroom/Core/Log.h"
#include "Shroom/Core/Application.h"

extern void Shroom::CreateApplication();

int main() {
    Shroom::Log::Init();

    Shroom::CreateApplication();

    Shroom::Log::Shutdown();
}
