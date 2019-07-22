cmake_minimum_required(VERSION 3.10.2)

add_executable(basic2 main.cpp)

set_target_properties(basic2
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
