cmake_minimum_required(VERSION 3.10.2)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if(NOT TARGET entity)
  add_subdirectory(../entity "${CMAKE_BINARY_DIR}/src/entity")
endif()

add_library(core SHARED ../include/fate/core.h core.cpp ../include/fate/scene.h scene.cpp)
target_include_directories(core PUBLIC ../include)
target_link_libraries(core PUBLIC entity)
