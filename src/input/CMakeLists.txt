cmake_minimum_required(VERSION 3.10.2)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(SDL2 REQUIRED)
add_library(input SHARED ../include/fate/input.h input.cpp)
target_include_directories(input PUBLIC ../include)
target_include_directories(input PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(input PRIVATE ${SDL2_LIBRARIES})
