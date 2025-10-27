cmake_minimum_required(VERSION 3.16)
project(f1sh-3d CXX)
set(CMAKE_CXX_STANDARD 17)
option(USE_SDL_BACKEND "Build with SDL backend" ON)

add_executable(f1sh-3d
  src/app.cpp
  # core + raster headers can be listed or just included via target_include_directories
)

target_include_directories(f1sh-3d PRIVATE src)

if(USE_SDL_BACKEND)
  find_package(SDL2 REQUIRED)
  target_sources(f1sh-3d PRIVATE
    src/platform/ibackend.hpp
    src/platform/sdl/backend_sdl.hpp
    src/platform/sdl/backend_sdl.cpp
  )
  target_link_libraries(f1sh-3d PRIVATE SDL2::SDL2)
else()
  target_sources(f1sh-3d PRIVATE
    src/platform/ibackend.hpp
    # src/platform/custom/backend_custom.cpp (future)
  )
endif()