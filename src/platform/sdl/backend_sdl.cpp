#include "platform/sdl/backend_sdl.hpp"
#include <SDL.h>

namespace plat {

static Key mapKey(SDL_Keycode k) {
    switch(k) {
        case SDLK_ESCAPE: return Key::Escape;
        case SDLK_w: return Key::W;
        case SDLK_a: return Key::A;
        case SDLK_s: return Key::S;
        case SDLK_d: return Key::D;
        default: return Key::Unknown;
    }
}

bool SDLBackend::init(const BackendConfig& cfg) {
    w_ = cfg.width;
    h_ = cfg.height;
    if(SDL_Init(SDL_INIT_VIDEO)!=0) return false;
    win_ = SDL_CreateWindow(cfg.title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w_, h_, 0);
    ren_ = SDL_CreateRenderer(win_, -1, SDL_RENDERER_ACCELERATED);
    tex_ = SDL_CreateTexture(ren_, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, w_, h_);
    return win_ && ren_ && tex_;
}

void SDLBackend::shutdown() {
    if(tex_) SDL_DestroyTexture(tex_);
    if(ren_) SDL_DestroyRenderer(ren_);
    if(win_) SDL_DestroyWindow(win_);
    SDL_Quit();
}

void SDLBackend::present(const uint32_t* rgba, int width, int height, int strideBytes) {
    if(width != w_ || height != h_) {
        if(tex_) SDL_DestroyTexture(tex_);
        w_=width;
        h_=height;
        tex_=SDL_CreateTexture(ren_, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, w_, h_);
    }
    SDL_UpdateTexture(tex_, nullptr, rgba, strideBytes);
    SDL_RendererClear(ren_);
    SDL_RendererCopy(ren_, tex_, nullptr, nullptr);
    SDL_RendererPresent(ren_);
}

td::optional<Event> SDLBackend::pollEvent(){
  SDL_Event e; if(!SDL_PollEvent(&e)) return std::nullopt;
  Event ev{};
  switch(e.type){
    case SDL_QUIT: ev.type = Event::Type::Quit; break;
    case SDL_KEYDOWN: ev.type = Event::Type::KeyDown; ev.key = mapKey(e.key.keysym.sym); break;
    case SDL_KEYUP:   ev.type = Event::Type::KeyUp;   ev.key = mapKey(e.key.keysym.sym); break;
    case SDL_MOUSEMOTION: ev.type=Event::Type::MouseMove; ev.mx=e.motion.x; ev.my=e.motion.y; ev.dx=e.motion.xrel; ev.dy=e.motion.yrel; break;
    case SDL_MOUSEBUTTONDOWN: ev.type=Event::Type::MouseDown; break;
    case SDL_MOUSEBUTTONUP:   ev.type=Event::Type::MouseUp;   break;
    case SDL_WINDOWEVENT:
      if(e.window.event==SDL_WINDOWEVENT_SIZE_CHANGED){
        ev.type=Event::Type::Resize; ev.width=e.window.data1; ev.height=e.window.data2;
      } break;
    default: break;
  }
  return ev;
}

double SDLBackend::nowSeconds() const {
    static const double invFreq = 1.0 / SDL_GetPerformanceFrequency();
    return SDL_GetPerformanceCounter() * invFreq;
}

void SDLBackend::setTitle(const std::string& title) {
    if(win_) SDL_SetWindowTitle(win_, title.c_str());
}

IBackend* createSDLBackend() {
    return new SDLBackend();
}

} // namespace plat