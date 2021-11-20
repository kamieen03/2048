cmake_minimum_required(VERSION 3.13)
project(2048)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE DEBUG)
set(COMPILE_FLAGS -Wall -Weffc++ -Wextra -Wsign-conversion -pedantic-errors)

add_executable(2048 Tile.cpp Grid.cpp Game.cpp KeyHandler.cpp main.cpp)

