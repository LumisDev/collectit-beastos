cmake_minimum_required(VERSION 3.5)
project(CollectitBeastos LANGUAGES CXX C)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

include(cmake_modules/get_cpm.cmake)
CPMAddPackage("gh:libsdl-org/SDL#release-2.30.0")
CPMAddPackage(
    NAME sdl2image
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
    GIT_TAG release-2.8.0
    GIT_SHALLOW YES
)
CPMAddPackage("gh:walterschell/Lua#master")

if(sdl2image_ADDED)
    execute_process(
        COMMAND git submodule update --init --recursive
        WORKING_DIRECTORY ${sdl2image_SOURCE_DIR}
        RESULT_VARIABLE result
    )
    if(result)
        message(FATAL_ERROR "Failed to initialize submodules in ${sdl2image_SOURCE_DIR}")
    endif()
endif()
add_executable(collectit-beastos src/main.cpp src/glad.c)
add_dependencies(collectit-beastos lua_static SDL2::SDL2)
target_include_directories(collectit-beastos PRIVATE include)
target_link_libraries(collectit-beastos PRIVATE lua_static SDL2::SDL2)
target_compile_definitions(collectit-beastos PRIVATE SDL_MAIN_HANDLED)
