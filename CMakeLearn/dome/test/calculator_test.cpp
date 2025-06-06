#include "gtest/gtest.h" // Gtest模块
#include "mylib/mylib.h" // 待测试的库

using namespace mylib;
int a, b, c;
TEST(CalculatorTest, Add) {
    Calculator calculator;
    int result = calculator.Add(a, b);
    EXPECT_EQ(result, c);
}
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    a = atoi(argv[1]);
    b = atoi(argv[2]);
    c = atoi(argv[3]);
    return RUN_ALL_TESTS();
}