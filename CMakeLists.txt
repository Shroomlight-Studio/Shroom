cmake_minimum_required(VERSION 3.30)
project(ShroomEngine)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ----- Force Static Build -----
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

# ----- Output Settings -----
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# ----- CPM.cmake -----
file(
  DOWNLOAD
  https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.40.8/CPM.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake
  EXPECTED_HASH SHA256=78ba32abdf798bc616bab7c73aac32a17bbd7b06ad9e26a6add69de8f3ae4791
)
include(${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake)

# ----- Dependencies -----
# glm
CPMAddPackage("gh:g-truc/glm#a532f5b")

# spdlog
CPMAddPackage("gh:gabime/spdlog@1.16.0")

# Vulkan-Headers
CPMAddPackage("gh:KhronosGroup/Vulkan-Headers@1.4.337")

# SDL3
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON CACHE BOOL "" FORCE)
CPMAddPackage("gh:libsdl-org/SDL#bd29d60")

# ----- Subdirectories -----
add_subdirectory(Shroom)
add_subdirectory(Sandbox)
