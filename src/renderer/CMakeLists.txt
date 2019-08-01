cmake_minimum_required(VERSION 3.10.2)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
if(NOT TARGET window)
  add_subdirectory(../window "${CMAKE_BINARY_DIR}/src/window")
endif()

if(NOT TARGET entity)
  add_subdirectory(../entity "${CMAKE_BINARY_DIR}/src/entity")
endif()

# find_package(SDL2 REQUIRED)

add_library(bgfx SHARED IMPORTED GLOBAL)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../libs/bgfx/.build/linux64_gcc/bin/libbgfx-shared-libRelease.so ${CMAKE_CURRENT_BINARY_DIR}/libbgfx-shared-libRelease.so COPYONLY)
set_target_properties(bgfx
  PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/libbgfx-shared-libRelease.so)

add_library(bimg STATIC IMPORTED GLOBAL)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../libs/bgfx/.build/linux64_gcc/bin/libbimg_decodeRelease.a ${CMAKE_CURRENT_BINARY_DIR}/libbimg_decodeRelease.a COPYONLY)
set_target_properties(bimg
  PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/libbimg_decodeRelease.a)

add_library(renderer SHARED ../include/fate/renderer.h renderer.cpp ../include/fate/shader.h shader.cpp)
target_include_directories(renderer PUBLIC ../include)
target_include_directories(renderer PRIVATE ../libs/bgfx/include ../libs/bx/include ../libs/bimg/include)
target_link_libraries(renderer PRIVATE window bgfx GL X11 bimg entity)
