#include <beastos/context_2d.hpp>
#include <stdexcept>


Context2D::Context2D(SDL_Window *window) {
    SDL_GetWindowSize(window, &win_width, &win_height);
    if (!initGL(window)) {
        throw std::runtime_error("OpenGL couldn't init normally!");
    }
    surface = SDL_CreateRGBSurfaceWithFormat(0, win_width*6, win_height*6, 32, SDL_PIXELFORMAT_RGBA32);
    if (!surface) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Surface couldn't be created! Cause:", SDL_GetError());
        exit(1);
    }
}

void Context2D::initSurface() {
    surface = SDL_CreateRGBSurfaceWithFormat(0, win_width*6, win_height*6, 32, SDL_PIXELFORMAT_RGBA32);
    
    if (!surface) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Surface couldn't be created! Cause:", SDL_GetError());
        exit(1);
    }
}
void Context2D::drawImage(const std::string &filepath) {
    SDL_Surface* imgSurf = IMG_Load(filepath.c_str());
    if (!imgSurf) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Surface couldn't be created! Cause", IMG_GetError());
    }
    SDL_BlitSurface(imgSurf, 0, surface, 0);
    SDL_FreeSurface(imgSurf);
}
void Context2D::draw(){

}

void Context2D::free() {

    SDL_Surface* paintsurf = SDL_CreateRGBSurfaceWithFormat(0, win_width*6, win_height*6, 32, SDL_PIXELFORMAT_RGBA32);
    SDL_BlitSurface(surface, 0, paintsurf, 0); // Blit onto a purely RGB Surface

    glGenTextures( 1, &texture );
    glBindTexture( GL_TEXTURE_2D, texture );
    glTexImage2D( GL_TEXTURE_2D, 0, 3, win_width*6, win_height*6, 0, GL_RGBA,
            GL_UNSIGNED_BYTE, paintsurf->pixels );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    SDL_FreeSurface(surface);
}
bool Context2D::initGL(SDL_Window* window) {
    SDL_GLContext ctx = SDL_GL_CreateContext(window);
    if (!ctx) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL couldn't create OpenGL context! Cause: %s", SDL_GetError());
        return false;
    }
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL couldn't load OpenGL! Cause: %s", SDL_GetError());
        return false;
    }


    
    glViewport(0, 0, win_width, win_height);
    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    return true;
}