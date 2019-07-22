cmake_minimum_required(VERSION 3.10.2)

project(Fate
  VERSION 1.0
  DESCRIPTION "A simple game engine"
  LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_EXTENSIONS "${WARNING_FLAGS}")

add_subdirectory(src)
add_subdirectory(examples)
