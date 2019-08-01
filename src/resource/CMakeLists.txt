cmake_minimum_required(VERSION 3.10.2)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if(NOT TARGET entity)
  add_subdirectory(../entity "${CMAKE_BINARY_DIR}/src/entity")
endif()

add_library(resource SHARED ../include/fate/resource.h resource.cpp)
target_include_directories(resource PUBLIC ../include)
target_link_libraries(resource PUBLIC entity)
target_link_libraries(resource PRIVATE bgfx bimg)
