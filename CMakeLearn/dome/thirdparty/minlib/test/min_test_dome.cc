#include "gtest/gtest.h"
#include "minlib/min.h"

int a, b, c;

TEST(MinLibTest, MinTest) {
    EXPECT_EQ(mymin(a, b), c);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  a = atoi(argv[1]);
  b = atoi(argv[2]);
  c = atoi(argv[3]);
  return RUN_ALL_TESTS();
}