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
CPMAddPackage("gh:g-truc/glm#master")

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
set(SHADER_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/shaders")
set(SHADER_OUTPUT_DIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/shaders")

# Create the destination directory if it doesn't exist
file(MAKE_DIRECTORY ${SHADER_OUTPUT_DIR})

# Gather all .vert and .frag files in the source directory
file(GLOB SHADER_FILES "${SHADER_SOURCE_DIR}/*.vert" "${SHADER_SOURCE_DIR}/*.frag")

# Define the copy_shaders target
add_custom_target(copy_shaders ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${SHADER_SOURCE_DIR} ${SHADER_OUTPUT_DIR}
    COMMENT "Copying shader files to runtime output directory"
)

add_executable(collectit-beastos src/main.cpp src/glad.c src/context_2d.cpp src/shader.cpp src/camera.cpp)
add_dependencies(collectit-beastos lua_static SDL2::SDL2 SDL2_image::SDL2_image glm::glm copy_shaders)
target_include_directories(collectit-beastos PRIVATE include)
target_link_libraries(collectit-beastos PRIVATE lua_static SDL2::SDL2 SDL2_image::SDL2_image glm::glm)
target_compile_definitions(collectit-beastos PRIVATE SDL_MAIN_HANDLED)


