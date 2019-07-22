cmake_minimum_required(VERSION 3.10.2)

add_executable(basic main.cpp)
target_link_libraries(basic PUBLIC fate)

set_target_properties(basic
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
