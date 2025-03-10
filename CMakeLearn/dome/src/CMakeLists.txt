# 收集所有源文件
file(GLOB_RECURSE SOURCES "*.cpp")
# 创建库目标
add_library(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PUBLIC domeFlag)