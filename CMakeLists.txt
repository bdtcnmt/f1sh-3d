cmake_minimum_required(VERSION 3.16)
project(f1sh-3d CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    add_compile_options(/w4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Wconversion -Wno-unused-parameter)
endif()

find_package(SDL2 REQUIRED)

add_executable(f1sh-3d
    src/app.cpp
    src/platform/sdl_app.cpp
)

target_include_directories(f1sh-3d PRIVATE src)
target_link_libraries(f1sh-3d PRIVATE SDL2::SDL2)