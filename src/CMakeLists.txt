cmake_minimum_required(VERSION 3.10.2)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(log)
add_subdirectory(window)
add_subdirectory(input)

add_library(fate SHARED include/fate/core.h core/core.cpp)
target_link_libraries(fate PUBLIC log window input)
target_include_directories(fate PUBLIC include)
