# 查找Google Test包
find_package(GTest)


# 添加测试可执行文件
add_executable(mylib_test calculator_test.cpp)

# 链接库和测试框架
target_link_libraries(mylib_test
  PRIVATE
    mylib
    GTest::GTest
)

enable_testing()
# 添加测试
add_test(NAME mylib_test COMMAND mylib_test)
