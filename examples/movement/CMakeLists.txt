cmake_minimum_required(VERSION 3.10.2)

add_executable(movement main.cpp)
target_link_libraries(movement PUBLIC fate)

if(NOT TARGET Shaders)
  add_subdirectory(${CMAKE_SOURCE_DIR}/src/shaders ${CMAKE_BINARY_DIR}/bin/shaders)
endif()

add_dependencies(movement Shaders)

add_custom_target(copy-runtime-files-movement ALL
  COMMAND cmake -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/textures ${CMAKE_BINARY_DIR}/bin/textures
  )

add_dependencies(movement copy-runtime-files-movement)

set_target_properties(movement
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
