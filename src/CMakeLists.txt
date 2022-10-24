add_library(fileEditor STATIC fileControl.cpp)
add_library(Shell STATIC shell.cpp)
add_executable(Editor main.cpp)
add_executable(test_main main_test.cpp)