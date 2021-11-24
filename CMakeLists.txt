cmake_minimum_required(VERSION 3.13)
project(2048)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE DEBUG)
set(COMPILE_FLAGS -Wall -Weffc++ -Wextra -Wsign-conversion -pedantic-errors)

cmake_minimum_required(VERSION 3.13)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable(2048 InfoScreen.cpp Tile.cpp Grid.cpp Game.cpp KeyHandler.cpp main.cpp)
target_link_libraries( 2048 ${OpenCV_LIBS} )



