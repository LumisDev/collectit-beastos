#include <SDL2/SDL.h>
#include <SDL_events.h>
#include <glad/glad.h>
#include <lua.hpp>
void initGL(SDL_Window* window) {
    SDL_GLContext ctx = SDL_GL_CreateContext(window);
    if (!ctx) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL couldn't create OpenGL context! Cause: %s", SDL_GetError());
        exit(1);
    }
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL couldn't load OpenGL! Cause: %s", SDL_GetError());
        exit(1);
    }
    
    glViewport(0, 0, 640, 480);
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL couldn't start immediately! Cause: %s", SDL_GetError());
        return 1;
    }
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, SDL_TRUE);
    SDL_Window* window = SDL_CreateWindow("Collectit Beastos", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
    if (!window) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL window wouldn't be created: %s", SDL_GetError());
    }
    initGL(window);
    bool quit = false;
    glClearColor(0.0, 0.0, 0.0, 1.0);
    SDL_Event e;
    while(!quit) {
        SDL_PollEvent(&e);
        if (e.type == SDL_QUIT) {
            quit = true;
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        SDL_GL_SwapWindow(window);
    }
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
