cmake_minimum_required(VERSION 3.10.2)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
if(NOT TARGET window)
  add_subdirectory(../window "${CMAKE_BINARY_DIR}/src/window")
endif()

if(NOT TARGET entity)
  add_subdirectory(../entity "${CMAKE_BINARY_DIR}/src/entity")
endif()

add_library(renderer SHARED ../include/fate/renderer.h renderer.cpp ../include/fate/shader.h shader.cpp)
target_include_directories(renderer PUBLIC ../include)
target_link_libraries(renderer PRIVATE window bgfx GL X11 bimg entity)
