cmake_minimum_required(VERSION 3.7)

project(SDL2Test)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} src)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/user/include/SDL2")

add_executable(SnakeGame src/main.cpp src/game.cpp src/controller.cpp src/renderer.cpp src/snake.cpp src/obstacle.cpp)
target_link_libraries(SnakeGame ${SDL2_LIBRARIES})