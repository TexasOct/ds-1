cmake_minimum_required(VERSION 3.21)
project(ds_1)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
add_subdirectory(src)

target_link_libraries(Editor fileEditor)
