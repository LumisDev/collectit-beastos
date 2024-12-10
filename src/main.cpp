#include "SDL_image.h"
#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <lua.hpp>
#include <beastos/context_2d.hpp>

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL couldn't start immediately! Cause: %s", SDL_GetError());
        return 1;
    }
    if (!IMG_Init(IMG_INIT_PNG)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL couldn't init image loading! Cause: %s", IMG_GetError());
        return 1;
    }
    
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, SDL_TRUE);
    SDL_Window* window = SDL_CreateWindow("Collectit Beastos", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
    if (!window) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL window wouldn't be created: %s", SDL_GetError());
    }
    Context2D ctx{window};
    bool quit = false;
    glClearColor(0.0, 0.0, 0.0, 1.0);
    SDL_Event e;
    while(!quit) {
        SDL_PollEvent(&e);
        if (e.type == SDL_QUIT) {
            quit = true;
        }
        ctx.initSurface();
        ctx.free();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ctx.draw();
        SDL_GL_SwapWindow(window);
    }
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
