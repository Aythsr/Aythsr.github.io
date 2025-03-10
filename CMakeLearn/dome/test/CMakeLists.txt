# 查找Google Test包
find_package(GTest REQUIRED)

# 添加测试可执行文件
add_executable(mylib_test calculator_test.cpp)

# 链接库和测试框架
target_link_libraries(mylib_test
  PRIVATE
  ${PROJECT_NAME}
  GTest::gtest
  # GTest::gtest_main
)

# 添加测试
add_test(NAME mylib_test1 COMMAND mylib_test 1 2 3)
add_test(NAME mylib_test2 COMMAND mylib_test 2 3 5)
add_test(NAME mylib_test3 COMMAND mylib_test 2 3 6)
