cmake_minimum_required(VERSION 3.24)
project(lab10)

set(CMAKE_CXX_STANDARD 14)

aux_source_directory(. DIR_SRCS)
include_directories(include)
add_subdirectory(liba)
add_subdirectory(libs)

add_executable(lab10 ${DIR_SRCS})

target_link_libraries(lab10 liba libs)