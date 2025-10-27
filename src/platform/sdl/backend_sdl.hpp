#pragma once
#include "platform/ibackend.hpp"

// forward decl to avoid leaking <SDL.h> to the rest of the engine
struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

namespace plat {

struct SDLBackend : IBackend {
    bool init(const BackendConfig& cfg) override;
    void shutdown() override;
    void present( const uint32_t* rgba, int width, int height, int stideBytes) override;
    std::optional<Event> pollEvent() override;
    double nowSeconds() const override;
    void setTitle(const std::string& title) override;
private:
    int w_=0, h_=0;
    SDL_Window* win_ = nullptr;
    SDL_Renderer* ren_ = nullptr;
    SDL_Texture* tex_ = nullptr;
};

IBackend* createSDLBackend(); // factory

} // namespace pla 
