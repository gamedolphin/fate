cmake_minimum_required(VERSION 3.10.2)

add_executable(basic main.cpp)
target_link_libraries(basic PUBLIC fate)

add_subdirectory(${CMAKE_SOURCE_DIR}/src/shaders ${CMAKE_BINARY_DIR}/bin/shaders)

add_dependencies(basic Shaders)

add_custom_target(copy-runtime-files ALL
  COMMAND cmake -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/textures ${CMAKE_BINARY_DIR}/bin/textures
  )

add_dependencies(basic copy-runtime-files)

set_target_properties(basic
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
