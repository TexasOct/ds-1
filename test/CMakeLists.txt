cmake_minimum_required(VERSION 3.24)
enable_testing()
find_package(GTest REQUIRED) #查找GTest的动态库
include_directories(${GTEST_INCLUDE_DIR})#Gtest的头文件
set(test_name test_ds)# 设置test名称
add_executable(${test_name} test.cpp) #生成测试文件
target_link_libraries(${test_name} ${GTEST_BOTH_LIBRARIES} fileEditor Shell) #链接测试依赖库
add_test(
        Name ${test_name}
        COMMAND ${test_name}
)