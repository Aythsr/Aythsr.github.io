# 添加示例可执行文件
add_executable(calculator_example calculator_example.cpp)

# 链接库
target_link_libraries(calculator_example
  PRIVATE
  ${PROJECT_NAME}
)