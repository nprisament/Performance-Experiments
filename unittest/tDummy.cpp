#include "Dialect/ExptDialect.h"
#include <gtest/gtest.h>

// Basic test fixture
class ExptTest : public ::testing::Test {
protected:
  void SetUp() override {
    // Setup code that will be called before each test
  }

  void TearDown() override {
    // Cleanup code that will be called after each test
  }
};

// Simple test case
TEST(ExptBasicTest, SimpleTest) {
  EXPECT_EQ(1 + 1, 2);
  EXPECT_TRUE(true);
}

// Test using the fixture
TEST_F(ExptTest, FixtureTest) {
  // Example of testing MLIR/Expt functionality
  // This is just a placeholder - you would typically test your actual dialect
  // operations here
  EXPECT_NO_THROW({
      // Any MLIR/Expt specific tests would go here
  });
}

// Parameterized test example
class ExptParamTest : public ::testing::TestWithParam<int> {};

TEST_P(ExptParamTest, ParamTest) {
  int value = GetParam();
  EXPECT_GE(value, 0);
}

INSTANTIATE_TEST_SUITE_P(ExptParamTests, ExptParamTest,
                         ::testing::Values(0, 1, 2, 3, 4));
