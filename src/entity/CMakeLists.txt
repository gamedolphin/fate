cmake_minimum_required(VERSION 3.10.2)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if(NOT TARGET EnTT)
  add_subdirectory(../libs/entt "${CMAKE_BINARY_DIR}/src/libs/entt")
endif()

add_library(entity SHARED entity.cpp ../include/fate/entity.h ../include/fate/component_transform.h ../include/fate/component_camera.h ../include/fate/component_render.h ../include/fate/math.h)
target_include_directories(entity PUBLIC ../include)
target_include_directories(entity PUBLIC ../libs/entt/src)
target_link_libraries(entity PUBLIC EnTT)
