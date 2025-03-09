# 查找Google Test包
find_package(GTest)


# 添加测试可执行文件
add_executable(mylib_test calculator_test.cpp)
add_executable(mylib_test1 calculator_test1.cpp)

# 链接库和测试框架
target_link_libraries(mylib_test
  PRIVATE
    mylib
    GTest::gtest
)
target_link_libraries(mylib_test1
  PRIVATE
    mylib
    GTest::gtest
)

enable_testing()
# 添加测试
add_test(NAME mylib_test COMMAND mylib_test)
add_test(NAME mylib_test1 COMMAND mylib_test1)
