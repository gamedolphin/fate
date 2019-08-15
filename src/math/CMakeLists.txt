cmake_minimum_required(VERSION 3.10.2)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(math SHARED ../include/fate/math.h ../include/fate/random.h random.cpp)
target_include_directories(math PRIVATE ../include)
set_target_properties(math
  PROPERTIES
  CXX_CLANG_TIDY "clang-tidy")
