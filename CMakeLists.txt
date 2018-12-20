cmake_minimum_required(VERSION 3.7)
project(Snake)

set(CMAKE_CXX_STANDARD 14)

#SFML stuff
set(CMAKE_MODULE_PATH "C:/SFML-2.4.2/cmake/Modules" ${CMAKE_MODULE_PATH})
find_package(SFML COMPONENTS graphics window system REQUIRED)
include_directories(${SFML_INCLUDE_DIR})

#header files
set(HEADERS
        source/SnakeLib/SnakeLib.hpp
        source/TileMap/TileMap.hpp)

#source files
set(SOURCES
        source/GameLoop.cpp
        source/SnakeLib/Fruit/Fruit.cpp
        source/SnakeLib/MoveableBlock/MoveableBlock.cpp
        source/SnakeLib/Snake/Snake.cpp
        source/TileMap/Map/Map.cpp
        source/TileMap/Tile/Tile.cpp)

#add files to executable
add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
