cmake_minimum_required(VERSION 3.30)
project(ShroomEngine)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
# spdlog
CPMAddPackage("gh:gabime/spdlog@1.16.0")

# SDL3
CPMAddPackage("gh:libsdl-org/SDL#bd29d60")

# Vulkan
CPMAddPackage("gh:KhronosGroup/Vulkan-Headers@1.4.337b")

# ----- Subdirectories -----
add_subdirectory(Shroom)
add_subdirectory(Sandbox)
