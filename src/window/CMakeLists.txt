cmake_minimum_required(VERSION 3.10.2)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(SDL2 REQUIRED)
add_library(window SHARED ../include/fate/window.h window.cpp)
target_include_directories(window PUBLIC ../include)
target_include_directories(window PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(window PRIVATE ${SDL2_LIBRARIES})
set_target_properties(window
  PROPERTIES
  CXX_CLANG_TIDY "clang-tidy")
