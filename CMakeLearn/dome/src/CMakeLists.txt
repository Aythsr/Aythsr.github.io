# 收集所有源文件
file(GLOB_RECURSE SOURCES "*.cpp")
# 创建库目标
add_library(mylib ${SOURCES})

target_link_libraries(mylib PUBLIC MylibFlag)