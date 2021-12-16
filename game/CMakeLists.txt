find_package( OpenCV REQUIRED )
include_directories( inc ${OpenCV_INCLUDE_DIRS} )
add_executable(2048 src/GameState.cpp
                    src/graphics.cpp
                    src/Menu.cpp
                    src/ColorSchemeReader.cpp
                    src/WinScreen.cpp
                    src/LoseScreen.cpp
                    src/Tile.cpp
                    src/Grid.cpp
                    src/GridDrawer.cpp
                    src/Game.cpp
                    src/KeyHandler.cpp
                    src/main.cpp)
target_link_libraries( 2048 ${OpenCV_LIBS} )

