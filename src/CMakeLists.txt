cmake_minimum_required(VERSION 3.10.2)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(log)
if(NOT TARGET window)
  add_subdirectory(window)
endif()
if(NOT TARGET entity)
  add_subdirectory(entity)
endif()
add_subdirectory(input)
add_subdirectory(renderer)
add_subdirectory(resource)
add_subdirectory(core)

add_library(fate SHARED fate.cpp)
target_link_libraries(fate PUBLIC log window input renderer resource core)
target_include_directories(fate PUBLIC include)
