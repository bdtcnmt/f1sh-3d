#pragma once
#include <SDL.h>
#include <cstdint>

struct SDLApp {
    int w{}, h{};
    SDL_Window* window{};
    SDL_Renderer* renderer{};
    SDL_Texture* texture{};
    
    bool init(const char* title, int W, int H);
    void present(const uint32_t* rgba); // expects WxH RGBA8
    void shutdown();
};