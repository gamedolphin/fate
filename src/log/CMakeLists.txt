cmake_minimum_required(VERSION 3.10.2)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(../libs/spdlog "${CMAKE_BINARY_DIR}/libs/spdlog")
add_library(log SHARED ../include/fate/log.h log.cpp)
target_include_directories(log PRIVATE ../include)
target_link_libraries(log PRIVATE spdlog::spdlog)
set_target_properties(log
  PROPERTIES
  CXX_CLANG_TIDY "clang-tidy")
