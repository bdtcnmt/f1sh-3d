// Wraps SDL2 to create the window, manage keyboard input, 
// and copy framebuffer pixels to the screen

#include "sdl_app.hpp"

bool SDLApp::init(const char* title, int W, int H) {
    w=W; h=H;
    if(SDL_Init(SDL_INIT_VIDEO) != 0) return false;
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W, H, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_REBDERER_ACCELERATED);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, W, H);
    return window && renderer && texture;
}

void SDLApp::present(const unint32_t* rgba) {
    SDL_UpdateTexture(texture, nullptr, rgba, w*4);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}

void SDLApp::shutdown() {
    if(texture) SDL_DestroyTexture(texture);
    if(renderer) SDL_DestroyRenderer(renderer);
    if(window) SDL_DestroyWindow(window);
    SDL_QUIT();
}