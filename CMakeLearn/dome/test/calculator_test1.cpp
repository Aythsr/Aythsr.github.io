#include "gtest/gtest.h"
#include "mylib/mylib.h"
#include <iostream>

using namespace mylib;

TEST(CalculatorTest, Add) {
    Calculator calculator;
    int result = calculator.Add(3, 3);
    EXPECT_EQ(result, 6);
}

int main(int argc, char **argv) {
    // std::cout << argv[1] << ' ' << argv[2] << std::endl;
    // 运行所有测试用例
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}