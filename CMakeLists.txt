cmake_minimum_required(VERSION 3.19)
project(SDLGame C)

set(CMAKE_C_STANDARD 99)
find_file(SDL2_INCLUDE_DIR NAME SDL.h HINTS SDL2)
find_library(SDL2_LIBRARY NAME SDL2)
find_package(SDL2 REQUIRED)
#find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(SDLGame main.c)
target_link_libraries(SDLGame SDL2)

