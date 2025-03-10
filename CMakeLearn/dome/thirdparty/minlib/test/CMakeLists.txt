add_executable(min_test "./min_test_dome.cc") 

find_package(GTest)

target_link_libraries(min_test PRIVATE ${PROJECT_NAME} GTest::gtest)


add_test(NAME minlib_t1 COMMAND min_test 1 2 1)
add_test(NAME minlib_t2 COMMAND min_test 2 2 1)