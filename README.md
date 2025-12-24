# Shroomlight Engine

A high-performance, modern C++23 game engine prototype built from scratch with **SDL3** and **Vulkan**.

> **Note:** This project is currently in active development as part of a 5-week intensive MVP sprint.

## Project Goals

The Shroomlight Engine is designed to demonstrate low-level software architecture, manual memory management, and modern GPU pipeline integration without the use of high-level engines like Unity or Unreal.

- **Graphics:** Vulkan 1.3+ with Dynamic Rendering (No legacy RenderPass boilerplate).
- **Architecture:** Layer-based system, with a clear separation between Engine and Client.
- **Standards:** Strictly C++23 using RAII patterns and smart memory management.
- **Build System:** Cross-platform CMake integration using CPM.cmake for dependency management.

## Tech Stack
* **Language:** C++23
* **Windowing/Input:** [SDL3](https://github.com/libsdl-org/SDL) (Latest preview)
* **Graphics API:** [Vulkan SDK](https://www.vulkan.org/)
* **Math:** [GLM](https://github.com/g-truc/glm)
* **Logging:** [spdlog](https://github.com/gabime/spdlog)
* **Build System:** CMake 3.30+

## Current Progress: Week 1

- [x] **Logging System:** High-performance asynchronous logger (spdlog) with Core/Client separation.
- [x] **Dependency Management:** CPM.cmake integration for zero-setup builds.
- [ ] **Core Architecture:** Entry point system and Application abstraction.
- [ ] **Windowing:** SDL3 window creation and event dispatcher.
- [ ] **Vulkan Context:** (In Progress) Instance and Device initialization.

## Getting Started

### Prerequisites

- **CMake** (v3.30 or higher)
- **Vulkan SDK** installed on your system.
- A C++23 compliant compiler (GCC 13+, Clang 16+, or MSVC 19.38+).

### Building

```bash
# Clone the repository
git clone https://github.com/Shroomlight-Studio/Shroom.git
cd Shroom

# Configure and Build
cmake -S . -B build
cmake --build build
```
