#pragma once
#include <cstdint>
#include <string>
#include <optional>

namespace plat {

enum class Key { Escape, W, A, S, D, Unknown };
enum class MouseButton { Left, Right, Middle, None };

struct Event {
    enum class Type { None, Quit, KeyDown, KeyUp, MouseMove, MouseDown, Resize } type = Type::None;
    Key key = Key::Unknown;
    MouseButton mouse = MouseButton::None;
    int mx = 0, my = 0, dx = 0, dy = 0; // mouse position and delta
    int width = 0, height = 0; // for resize
};

struct BackendConfig { 
    int width = 900, height = 540; 
    std::string title="f1sh-3d";
};

struct IBackend {
    virtual ~IBackend() = default;
    virtual bool init(const BackendConfig& cfg) = 0;
    virtual void shutdown() = 0;
    virtual void present(const uint32_t* rgba, int width, int height, int strideBytes) = 0;
    virtual std::optional<Event> pollEvent() = 0;
    virtual double nowSeconds() const = 0;
    virtual void setTitle(const std::string& title) = 0;
};

} // namespace plat