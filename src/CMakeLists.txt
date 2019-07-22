cmake_minimum_required(VERSION 3.10.2)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(fate SHARED include/fate/core.h core/core.cpp)

add_subdirectory(libs/spdlog)
spdlog_enable_warnings(fate)
add_library(log SHARED include/fate/log.h log/log.cpp)
target_include_directories(log PRIVATE include)
target_link_libraries(log PRIVATE spdlog::spdlog)

target_link_libraries(fate PUBLIC log)
target_include_directories(fate PUBLIC include)
