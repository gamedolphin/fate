cmake_minimum_required(VERSION 3.10.2)

add_executable(pong main.cpp gamescene.h gamescene.cpp)
target_link_libraries(pong PUBLIC fate)
target_include_directories(pong PUBLIC .)

if(NOT TARGET Shaders)
  add_subdirectory(${CMAKE_SOURCE_DIR}/src/shaders ${CMAKE_BINARY_DIR}/bin/shaders)
endif()

add_dependencies(pong Shaders)

add_custom_target(copy-runtime-files-pong ALL
  COMMAND cmake -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/textures ${CMAKE_BINARY_DIR}/bin/textures
  )

add_dependencies(pong copy-runtime-files-pong)

set_target_properties(pong
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
