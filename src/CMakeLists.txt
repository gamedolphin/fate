cmake_minimum_required(VERSION 3.10.2)

add_library(fate SHARED include/fate/core.h core/core.cpp)
target_include_directories(fate PUBLIC include)
