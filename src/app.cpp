#include "platform/ibackend.hpp"
#include "platform/sdl/backend_sdl.hpp"
#include "core/framebuffer.hpp"
#include "core/raster.hpp"

int main() {
    plat::IBackend* backend = plat::createSDLBackend();

    plat::BackendConfig cfg{900,540,"f1sh-3d"};
    if(!backend->init(cfg)) return 1;

    Framebuffer fb(cfg.width, cfg.height);

    bool running = true;
    while(running) {
        // pump events
        while(auto ev = backend->pollEvent()) {
            if(ev->type == plat::Event::Type::Quit) running = false;
            if(ev->type == plat::Event::Type::KeyDown && ev->key == plat::Key::Escape) running = false;
            if(ev->type == plat::Event::Type::Resize) {
                fb = Framebuffer(ev->width, ev->height); // reallocate CPU buffer
            }
        }

        fb.clear(0xff101018);
        // draw triangle/cube lines into fb here..
        backend->present(fb.color.data(), fb.w, fb.h, fb.w * 4);
    }

    backend->shutdown();
    delete backend;
    return 0;
}