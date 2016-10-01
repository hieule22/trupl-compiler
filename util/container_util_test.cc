// Unit tests for container utilities.
// Copyright Hieu Le 2016.

#include "util/container_util.h"

#include <vector>

#include "gtest/gtest.h"

namespace truplc {
namespace {

TEST(ContainTest, Basic) {
  std::vector<int> container = {1, 2, 3};
  EXPECT_TRUE(Contain(container, 3));
  EXPECT_FALSE(Contain(container, 0));
}

}  // namespace
}  // namespace truplc
