file(GLOB_RECURSE ENGINE_SOURCES "src/*.cpp")
file(GLOB_RECURSE ENGINE_HEADERS "src/*.h")

add_library(Shroom STATIC ${ENGINE_SOURCES} ${ENGINE_HEADERS})

target_include_directories(Shroom PUBLIC src)

target_link_libraries(Shroom
    PUBLIC
        glm::glm
        spdlog::spdlog
        SDL3::SDL3
)
