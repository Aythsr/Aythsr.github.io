#include "gtest/gtest.h"
#include "mylib/mylib.h"

using namespace mylib;

TEST(CalculatorTest, Add) {
    Calculator calculator;
    int result = calculator.Add(2, 3);
    EXPECT_EQ(result, 5);
}

int main() {
    // 运行所有测试用例
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}