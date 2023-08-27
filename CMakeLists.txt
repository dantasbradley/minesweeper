cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(P3Minesweeper)

## If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
#set(SFML_DIR "<sfml root prefix>/lib/cmake/SFML")
set(SFML_DIR "/opt/SFML")

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
add_executable(Minesweeper src/main.cpp src/Tile.h src/Tile.cpp src/Board.h src/Board.cpp src/TextureManager.h src/TextureManager.cpp src/Random.h src/Random.cpp src/Counter.h src/Counter.cpp)
target_link_libraries(Minesweeper sfml-graphics sfml-audio)
