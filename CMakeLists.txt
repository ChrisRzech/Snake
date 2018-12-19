cmake_minimum_required(VERSION 3.7)
project(Snake)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH "C:/SFML-2.4.2/cmake/Modules" ${CMAKE_MODULE_PATH})

find_package(SFML COMPONENTS graphics window system REQUIRED)
include_directories(${SFML_INCLUDE_DIR})

#header files
set(HEADERS
        src/SnakeLib/SnakeLib.hpp
        src/TileMap/TileMap.hpp)

#source files
set(SOURCES
        src/GameLoop.cpp
        src/SnakeLib/Fruit/Fruit.cpp
        src/SnakeLib/MoveableBlock/MoveableBlock.cpp
        src/SnakeLib/Snake/Snake.cpp
        src/TileMap/Map/Map.cpp
        src/TileMap/Tile/Tile.cpp)

#add files to executable
add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
