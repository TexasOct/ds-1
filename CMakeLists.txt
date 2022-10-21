cmake_minimum_required(VERSION 3.24)
project(ds_1)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
add_subdirectory(src)
add_subdirectory(test)

enable_testing()
target_link_libraries(main fileEditor)
