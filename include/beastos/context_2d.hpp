#pragma once
#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <SDL_image.h>
#include <string>
class Context2D {
    public:
        Context2D(SDL_Window *window);
        void initSurface();
        void drawImage(const std::string &filepath);
        void free();
        void draw();
    private:
        bool initGL(SDL_Window *window);
        SDL_Surface* surface = nullptr;
        GLuint texture = 0;
        int win_width = 0, win_height = 0;
};

